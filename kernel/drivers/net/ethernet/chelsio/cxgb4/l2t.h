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
#ifndef __CXGB4_L2T_H
#define __CXGB4_L2T_H

#include <beep/spinlock.h>
#include <beep/if_ether.h>
#include <beep/atomic.h>

struct adapter;
struct l2t_data;
struct neighbour;
struct net_device;
struct file_operations;
struct cpl_l2t_write_rpl;

/*
 * Each L2T entry plays multiple roles.  First of all, it keeps state for the
 * corresponding entry of the HW L2 table and maintains a queue of offload
 * packets awaiting address resolution.  Second, it is a node of a hash table
 * chain, where the nodes of the chain are linked together through their next
 * pointer.  Finally, each node is a bucket of a hash table, pointing to the
 * first element in its chain through its first pointer.
 */
struct l2t_entry {
	u16 state;                  /* entry state */
	u16 idx;                    /* entry index */
	u32 addr[4];                /* next hop IP or IPv6 address */
	int ifindex;                /* neighbor's net_device's ifindex */
	struct neighbour *neigh;    /* associated neighbour */
	struct l2t_entry *first;    /* start of hash chain */
	struct l2t_entry *next;     /* next l2t_entry on chain */
	struct sk_buff *arpq_head;  /* queue of packets awaiting resolution */
	struct sk_buff *arpq_tail;
	spinlock_t lock;
	atomic_t refcnt;            /* entry reference count */
	u16 hash;                   /* hash bucket the entry is on */
	u16 vlan;                   /* VLAN TCI (id: bits 0-11, prio: 13-15 */
	u8 v6;                      /* whether entry is for IPv6 */
	u8 lport;                   /* associated offload logical interface */
	u8 dmac[ETH_ALEN];          /* neighbour's MAC address */
};

typedef void (*arp_err_handler_t)(void *handle, struct sk_buff *skb);

/*
 * Callback stored in an skb to handle address resolution failure.
 */
struct l2t_skb_cb {
	void *handle;
	arp_err_handler_t arp_err_handler;
};

#define L2T_SKB_CB(skb) ((struct l2t_skb_cb *)(skb)->cb)

static inline void t4_set_arp_err_handler(struct sk_buff *skb, void *handle,
					  arp_err_handler_t handler)
{
	L2T_SKB_CB(skb)->handle = handle;
	L2T_SKB_CB(skb)->arp_err_handler = handler;
}

void cxgb4_l2t_release(struct l2t_entry *e);
int cxgb4_l2t_send(struct net_device *dev, struct sk_buff *skb,
		   struct l2t_entry *e);
struct l2t_entry *cxgb4_l2t_get(struct l2t_data *d, struct neighbour *neigh,
				const struct net_device *physdev,
				unsigned int priority);

void t4_l2t_update(struct adapter *adap, struct neighbour *neigh);
struct l2t_entry *t4_l2t_alloc_switching(struct l2t_data *d);
int t4_l2t_set_switching(struct adapter *adap, struct l2t_entry *e, u16 vlan,
			 u8 port, u8 *eth_addr);
struct l2t_data *t4_init_l2t(void);
void do_l2t_write_rpl(struct adapter *p, const struct cpl_l2t_write_rpl *rpl);

extern const struct file_operations t4_l2t_fops;
#endif  /* __CXGB4_L2T_H */
