/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <beep/export.h>
#include "pnfs.h"

#define NFSDBG_FACILITY		NFSDBG_PNFS

/*
 * Device ID RCU cache. A device ID is unique per server and layout type.
 */
#define NFS4_DEVICE_ID_HASH_BITS	5
#define NFS4_DEVICE_ID_HASH_SIZE	(1 << NFS4_DEVICE_ID_HASH_BITS)
#define NFS4_DEVICE_ID_HASH_MASK	(NFS4_DEVICE_ID_HASH_SIZE - 1)

#define PNFS_DEVICE_RETRY_TIMEOUT (120*HZ)

static struct hlist_head nfs4_deviceid_cache[NFS4_DEVICE_ID_HASH_SIZE];
static DEFINE_SPINLOCK(nfs4_deviceid_lock);

#ifdef NFS_DEBUG
void
nfs4_print_deviceid(const struct nfs4_deviceid *id)
{
	u32 *p = (u32 *)id;

	dprintk("%s: device id= [%x%x%x%x]\n", __func__,
		p[0], p[1], p[2], p[3]);
}
EXPORT_SYMBOL_GPL(nfs4_print_deviceid);
#endif

static inline u32
nfs4_deviceid_hash(const struct nfs4_deviceid *id)
{
	unsigned char *cptr = (unsigned char *)id->data;
	unsigned int nbytes = NFS4_DEVICEID4_SIZE;
	u32 x = 0;

	while (nbytes--) {
		x *= 37;
		x += *cptr++;
	}
	return x & NFS4_DEVICE_ID_HASH_MASK;
}

static struct nfs4_deviceid_node *
_lookup_deviceid(const struct pnfs_layoutdriver_type *ld,
		 const struct nfs_client *clp, const struct nfs4_deviceid *id,
		 long hash)
{
	struct nfs4_deviceid_node *d;
	struct hlist_node *n;

	hlist_for_each_entry_rcu(d, n, &nfs4_deviceid_cache[hash], node)
		if (d->ld == ld && d->nfs_client == clp &&
		    !memcmp(&d->deviceid, id, sizeof(*id))) {
			if (atomic_read(&d->ref))
				return d;
			else
				continue;
		}
	return NULL;
}

/*
 * Lookup a deviceid in cache and get a reference count on it if found
 *
 * @clp nfs_client associated with deviceid
 * @id deviceid to look up
 */
static struct nfs4_deviceid_node *
_find_get_deviceid(const struct pnfs_layoutdriver_type *ld,
		   const struct nfs_client *clp, const struct nfs4_deviceid *id,
		   long hash)
{
	struct nfs4_deviceid_node *d;

	rcu_read_lock();
	d = _lookup_deviceid(ld, clp, id, hash);
	if (d != NULL)
		atomic_inc(&d->ref);
	rcu_read_unlock();
	return d;
}

struct nfs4_deviceid_node *
nfs4_find_get_deviceid(const struct pnfs_layoutdriver_type *ld,
		       const struct nfs_client *clp, const struct nfs4_deviceid *id)
{
	return _find_get_deviceid(ld, clp, id, nfs4_deviceid_hash(id));
}
EXPORT_SYMBOL_GPL(nfs4_find_get_deviceid);

/*
 * Remove a deviceid from cache
 *
 * @clp nfs_client associated with deviceid
 * @id the deviceid to unhash
 *
 * @ret the unhashed node, if found and dereferenced to zero, NULL otherwise.
 */
void
nfs4_delete_deviceid(const struct pnfs_layoutdriver_type *ld,
			 const struct nfs_client *clp, const struct nfs4_deviceid *id)
{
	struct nfs4_deviceid_node *d;

	spin_lock(&nfs4_deviceid_lock);
	rcu_read_lock();
	d = _lookup_deviceid(ld, clp, id, nfs4_deviceid_hash(id));
	rcu_read_unlock();
	if (!d) {
		spin_unlock(&nfs4_deviceid_lock);
		return;
	}
	hlist_del_init_rcu(&d->node);
	spin_unlock(&nfs4_deviceid_lock);
	synchronize_rcu();

	/* balance the initial ref set in pnfs_insert_deviceid */
	if (atomic_dec_and_test(&d->ref))
		d->ld->free_deviceid_node(d);
}
EXPORT_SYMBOL_GPL(nfs4_delete_deviceid);

void
nfs4_init_deviceid_node(struct nfs4_deviceid_node *d,
			const struct pnfs_layoutdriver_type *ld,
			const struct nfs_client *nfs_client,
			const struct nfs4_deviceid *id)
{
	INIT_HLIST_NODE(&d->node);
	INIT_HLIST_NODE(&d->tmpnode);
	d->ld = ld;
	d->nfs_client = nfs_client;
	d->flags = 0;
	d->deviceid = *id;
	atomic_set(&d->ref, 1);
}
EXPORT_SYMBOL_GPL(nfs4_init_deviceid_node);

/*
 * Uniquely initialize and insert a deviceid node into cache
 *
 * @new new deviceid node
 *      Note that the caller must set up the following members:
 *        new->ld
 *        new->nfs_client
 *        new->deviceid
 *
 * @ret the inserted node, if none found, otherwise, the found entry.
 */
struct nfs4_deviceid_node *
nfs4_insert_deviceid_node(struct nfs4_deviceid_node *new)
{
	struct nfs4_deviceid_node *d;
	long hash;

	spin_lock(&nfs4_deviceid_lock);
	hash = nfs4_deviceid_hash(&new->deviceid);
	d = _find_get_deviceid(new->ld, new->nfs_client, &new->deviceid, hash);
	if (d) {
		spin_unlock(&nfs4_deviceid_lock);
		return d;
	}

	hlist_add_head_rcu(&new->node, &nfs4_deviceid_cache[hash]);
	spin_unlock(&nfs4_deviceid_lock);
	atomic_inc(&new->ref);

	return new;
}
EXPORT_SYMBOL_GPL(nfs4_insert_deviceid_node);

/*
 * Dereference a deviceid node and delete it when its reference count drops
 * to zero.
 *
 * @d deviceid node to put
 *
 * return true iff the node was deleted
 * Note that since the test for d->ref == 0 is sufficient to establish
 * that the node is no longer hashed in the global device id cache.
 */
bool
nfs4_put_deviceid_node(struct nfs4_deviceid_node *d)
{
	if (!atomic_dec_and_test(&d->ref))
		return false;
	d->ld->free_deviceid_node(d);
	return true;
}
EXPORT_SYMBOL_GPL(nfs4_put_deviceid_node);

void
nfs4_mark_deviceid_unavailable(struct nfs4_deviceid_node *node)
{
	node->timestamp_unavailable = jiffies;
	set_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags);
}
EXPORT_SYMBOL_GPL(nfs4_mark_deviceid_unavailable);

bool
nfs4_test_deviceid_unavailable(struct nfs4_deviceid_node *node)
{
	if (test_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags)) {
		unsigned long start, end;

		end = jiffies;
		start = end - PNFS_DEVICE_RETRY_TIMEOUT;
		if (time_in_range(node->timestamp_unavailable, start, end))
			return true;
		clear_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags);
	}
	return false;
}
EXPORT_SYMBOL_GPL(nfs4_test_deviceid_unavailable);

static void
_deviceid_purge_client(const struct nfs_client *clp, long hash)
{
	struct nfs4_deviceid_node *d;
	struct hlist_node *n;
	HLIST_HEAD(tmp);

	spin_lock(&nfs4_deviceid_lock);
	rcu_read_lock();
	hlist_for_each_entry_rcu(d, n, &nfs4_deviceid_cache[hash], node)
		if (d->nfs_client == clp && atomic_read(&d->ref)) {
			hlist_del_init_rcu(&d->node);
			hlist_add_head(&d->tmpnode, &tmp);
		}
	rcu_read_unlock();
	spin_unlock(&nfs4_deviceid_lock);

	if (hlist_empty(&tmp))
		return;

	synchronize_rcu();
	while (!hlist_empty(&tmp)) {
		d = hlist_entry(tmp.first, struct nfs4_deviceid_node, tmpnode);
		hlist_del(&d->tmpnode);
		if (atomic_dec_and_test(&d->ref))
			d->ld->free_deviceid_node(d);
	}
}

void
nfs4_deviceid_purge_client(const struct nfs_client *clp)
{
	long h;

	if (!(clp->cl_exchange_flags & EXCHGID4_FLAG_USE_PNFS_MDS))
		return;
	for (h = 0; h < NFS4_DEVICE_ID_HASH_SIZE; h++)
		_deviceid_purge_client(clp, h);
}

/*
 * Stop use of all deviceids associated with an nfs_client
 */
void
nfs4_deviceid_mark_client_invalid(struct nfs_client *clp)
{
	struct nfs4_deviceid_node *d;
	struct hlist_node *n;
	int i;

	rcu_read_lock();
	for (i = 0; i < NFS4_DEVICE_ID_HASH_SIZE; i ++){
		hlist_for_each_entry_rcu(d, n, &nfs4_deviceid_cache[i], node)
			if (d->nfs_client == clp)
				set_bit(NFS_DEVICEID_INVALID, &d->flags);
	}
	rcu_read_unlock();
}

