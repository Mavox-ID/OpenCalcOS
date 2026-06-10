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
#ifndef _ARP_H
#define _ARP_H

#include <beep/if_arp.h>
#include <beep/hash.h>
#include <net/neighbour.h>


extern struct neigh_table arp_tbl;

static inline u32 arp_hashfn(u32 key, const struct net_device *dev, u32 hash_rnd)
{
	u32 val = key ^ hash32_ptr(dev);

	return val * hash_rnd;
}

static inline struct neighbour *__ipv4_neigh_lookup_noref(struct net_device *dev, u32 key)
{
	struct neigh_hash_table *nht = rcu_dereference_bh(arp_tbl.nht);
	struct neighbour *n;
	u32 hash_val;

	hash_val = arp_hashfn(key, dev, nht->hash_rnd[0]) >> (32 - nht->hash_shift);
	for (n = rcu_dereference_bh(nht->hash_buckets[hash_val]);
	     n != NULL;
	     n = rcu_dereference_bh(n->next)) {
		if (n->dev == dev && *(u32 *)n->primary_key == key)
			return n;
	}

	return NULL;
}

static inline struct neighbour *__ipv4_neigh_lookup(struct net_device *dev, u32 key)
{
	struct neighbour *n;

	rcu_read_lock_bh();
	n = __ipv4_neigh_lookup_noref(dev, key);
	if (n && !atomic_inc_not_zero(&n->refcnt))
		n = NULL;
	rcu_read_unlock_bh();

	return n;
}

extern void	arp_init(void);
extern int	arp_find(unsigned char *haddr, struct sk_buff *skb);
extern int	arp_ioctl(struct net *net, unsigned int cmd, void __user *arg);
extern void     arp_send(int type, int ptype, __be32 dest_ip,
			 struct net_device *dev, __be32 src_ip,
			 const unsigned char *dest_hw,
			 const unsigned char *src_hw, const unsigned char *th);
extern int	arp_mc_map(__be32 addr, u8 *haddr, struct net_device *dev, int dir);
extern void	arp_ifdown(struct net_device *dev);

extern struct sk_buff *arp_create(int type, int ptype, __be32 dest_ip,
				  struct net_device *dev, __be32 src_ip,
				  const unsigned char *dest_hw,
				  const unsigned char *src_hw,
				  const unsigned char *target_hw);
extern void arp_xmit(struct sk_buff *skb);
int arp_invalidate(struct net_device *dev, __be32 ip);

#endif	/* _ARP_H */
