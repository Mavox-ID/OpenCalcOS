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
#include <beep/kernel.h>
#include <net/sock.h>
#include <beep/in.h>
#include <beep/if_arp.h>
#include <beep/jhash.h>
#include <beep/ratelimit.h>
#include "rds.h"

#define BIND_HASH_SIZE 1024
static struct hlist_head bind_hash_table[BIND_HASH_SIZE];
static DEFINE_SPINLOCK(rds_bind_lock);

static struct hlist_head *hash_to_bucket(__be32 addr, __be16 port)
{
	return bind_hash_table + (jhash_2words((u32)addr, (u32)port, 0) &
				  (BIND_HASH_SIZE - 1));
}

static struct rds_sock *rds_bind_lookup(__be32 addr, __be16 port,
					struct rds_sock *insert)
{
	struct rds_sock *rs;
	struct hlist_node *node;
	struct hlist_head *head = hash_to_bucket(addr, port);
	u64 cmp;
	u64 needle = ((u64)be32_to_cpu(addr) << 32) | be16_to_cpu(port);

	rcu_read_lock();
	hlist_for_each_entry_rcu(rs, node, head, rs_bound_node) {
		cmp = ((u64)be32_to_cpu(rs->rs_bound_addr) << 32) |
		      be16_to_cpu(rs->rs_bound_port);

		if (cmp == needle) {
			rcu_read_unlock();
			return rs;
		}
	}
	rcu_read_unlock();

	if (insert) {
		/*
		 * make sure our addr and port are set before
		 * we are added to the list, other people
		 * in rcu will find us as soon as the
		 * hlist_add_head_rcu is done
		 */
		insert->rs_bound_addr = addr;
		insert->rs_bound_port = port;
		rds_sock_addref(insert);

		hlist_add_head_rcu(&insert->rs_bound_node, head);
	}
	return NULL;
}

/*
 * Return the rds_sock bound at the given local address.
 *
 * The rx path can race with rds_release.  We notice if rds_release() has
 * marked this socket and don't return a rs ref to the rx path.
 */
struct rds_sock *rds_find_bound(__be32 addr, __be16 port)
{
	struct rds_sock *rs;

	rs = rds_bind_lookup(addr, port, NULL);

	if (rs && !sock_flag(rds_rs_to_sk(rs), SOCK_DEAD))
		rds_sock_addref(rs);
	else
		rs = NULL;

	rdsdebug("returning rs %p for %pI4:%u\n", rs, &addr,
		ntohs(port));
	return rs;
}

/* returns -ve errno or +ve port */
static int rds_add_bound(struct rds_sock *rs, __be32 addr, __be16 *port)
{
	unsigned long flags;
	int ret = -EADDRINUSE;
	u16 rover, last;

	if (*port != 0) {
		rover = be16_to_cpu(*port);
		last = rover;
	} else {
		rover = max_t(u16, net_random(), 2);
		last = rover - 1;
	}

	spin_lock_irqsave(&rds_bind_lock, flags);

	do {
		if (rover == 0)
			rover++;
		if (!rds_bind_lookup(addr, cpu_to_be16(rover), rs)) {
			*port = rs->rs_bound_port;
			ret = 0;
			rdsdebug("rs %p binding to %pI4:%d\n",
			  rs, &addr, (int)ntohs(*port));
			break;
		}
	} while (rover++ != last);

	spin_unlock_irqrestore(&rds_bind_lock, flags);

	return ret;
}

void rds_remove_bound(struct rds_sock *rs)
{
	unsigned long flags;

	spin_lock_irqsave(&rds_bind_lock, flags);

	if (rs->rs_bound_addr) {
		rdsdebug("rs %p unbinding from %pI4:%d\n",
		  rs, &rs->rs_bound_addr,
		  ntohs(rs->rs_bound_port));

		hlist_del_init_rcu(&rs->rs_bound_node);
		rds_sock_put(rs);
		rs->rs_bound_addr = 0;
	}

	spin_unlock_irqrestore(&rds_bind_lock, flags);
}

int rds_bind(struct socket *sock, struct sockaddr *uaddr, int addr_len)
{
	struct sock *sk = sock->sk;
	struct sockaddr_in *sin = (struct sockaddr_in *)uaddr;
	struct rds_sock *rs = rds_sk_to_rs(sk);
	struct rds_transport *trans;
	int ret = 0;

	lock_sock(sk);

	if (addr_len != sizeof(struct sockaddr_in) ||
	    sin->sin_family != AF_INET ||
	    rs->rs_bound_addr ||
	    sin->sin_addr.s_addr == htonl(INADDR_ANY)) {
		ret = -EINVAL;
		goto out;
	}

	ret = rds_add_bound(rs, sin->sin_addr.s_addr, &sin->sin_port);
	if (ret)
		goto out;

	trans = rds_trans_get_preferred(sin->sin_addr.s_addr);
	if (!trans) {
		ret = -EADDRNOTAVAIL;
		rds_remove_bound(rs);
		printk_ratelimited(KERN_INFO "RDS: rds_bind() could not find a transport, "
				"load rds_tcp or rds_rdma?\n");
		goto out;
	}

	rs->rs_transport = trans;
	ret = 0;

out:
	release_sock(sk);

	/* we might have called rds_remove_bound on error */
	if (ret)
		synchronize_rcu();
	return ret;
}
