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
#ifndef _TIPC_NODE_H
#define _TIPC_NODE_H

#include "node_subscr.h"
#include "addr.h"
#include "net.h"
#include "bearer.h"

/*
 * Out-of-range value for node signature
 */
#define INVALID_NODE_SIG 0x10000

/* Flags used to block (re)establishment of contact with a neighboring node */
#define WAIT_PEER_DOWN	0x0001	/* wait to see that peer's links are down */
#define WAIT_NAMES_GONE	0x0002	/* wait for peer's publications to be purged */
#define WAIT_NODE_DOWN	0x0004	/* wait until peer node is declared down */

/**
 * struct tipc_node - TIPC node structure
 * @addr: network address of node
 * @lock: spinlock governing access to structure
 * @hash: links to adjacent nodes in unsorted hash chain
 * @list: links to adjacent nodes in sorted list of cluster's nodes
 * @nsub: list of "node down" subscriptions monitoring node
 * @active_links: pointers to active links to node
 * @links: pointers to all links to node
 * @working_links: number of working links to node (both active and standby)
 * @block_setup: bit mask of conditions preventing link establishment to node
 * @link_cnt: number of links to node
 * @permit_changeover: non-zero if node has redundant links to this system
 * @signature: node instance identifier
 * @bclink: broadcast-related info
 *    @acked: sequence # of last outbound b'cast message acknowledged by node
 *    @last_in: sequence # of last in-sequence b'cast message received from node
 *    @last_sent: sequence # of last b'cast message sent by node
 *    @oos_state: state tracker for handling OOS b'cast messages
 *    @deferred_size: number of OOS b'cast messages in deferred queue
 *    @deferred_head: oldest OOS b'cast message received from node
 *    @deferred_tail: newest OOS b'cast message received from node
 *    @defragm: list of partially reassembled b'cast message fragments from node
 *    @recv_permitted: true if node is allowed to receive b'cast messages
 */
struct tipc_node {
	u32 addr;
	spinlock_t lock;
	struct hlist_node hash;
	struct list_head list;
	struct list_head nsub;
	struct tipc_link *active_links[2];
	struct tipc_link *links[MAX_BEARERS];
	int link_cnt;
	int working_links;
	int block_setup;
	int permit_changeover;
	u32 signature;
	struct {
		u32 acked;
		u32 last_in;
		u32 last_sent;
		u32 oos_state;
		u32 deferred_size;
		struct sk_buff *deferred_head;
		struct sk_buff *deferred_tail;
		struct sk_buff *defragm;
		bool recv_permitted;
	} bclink;
};

extern struct list_head tipc_node_list;

struct tipc_node *tipc_node_find(u32 addr);
struct tipc_node *tipc_node_create(u32 addr);
void tipc_node_delete(struct tipc_node *n_ptr);
void tipc_node_attach_link(struct tipc_node *n_ptr, struct tipc_link *l_ptr);
void tipc_node_detach_link(struct tipc_node *n_ptr, struct tipc_link *l_ptr);
void tipc_node_link_down(struct tipc_node *n_ptr, struct tipc_link *l_ptr);
void tipc_node_link_up(struct tipc_node *n_ptr, struct tipc_link *l_ptr);
int tipc_node_active_links(struct tipc_node *n_ptr);
int tipc_node_redundant_links(struct tipc_node *n_ptr);
int tipc_node_is_up(struct tipc_node *n_ptr);
struct sk_buff *tipc_node_get_links(const void *req_tlv_area, int req_tlv_space);
struct sk_buff *tipc_node_get_nodes(const void *req_tlv_area, int req_tlv_space);

static inline void tipc_node_lock(struct tipc_node *n_ptr)
{
	spin_lock_bh(&n_ptr->lock);
}

static inline void tipc_node_unlock(struct tipc_node *n_ptr)
{
	spin_unlock_bh(&n_ptr->lock);
}

#endif
