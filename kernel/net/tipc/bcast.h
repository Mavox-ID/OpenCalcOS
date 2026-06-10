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
#ifndef _TIPC_BCAST_H
#define _TIPC_BCAST_H

#define MAX_NODES 4096
#define WSIZE 32

/**
 * struct tipc_node_map - set of node identifiers
 * @count: # of nodes in set
 * @map: bitmap of node identifiers that are in the set
 */
struct tipc_node_map {
	u32 count;
	u32 map[MAX_NODES / WSIZE];
};

#define PLSIZE 32

/**
 * struct tipc_port_list - set of node local destination ports
 * @count: # of ports in set (only valid for first entry in list)
 * @next: pointer to next entry in list
 * @ports: array of port references
 */
struct tipc_port_list {
	int count;
	struct tipc_port_list *next;
	u32 ports[PLSIZE];
};


struct tipc_node;

extern const char tipc_bclink_name[];

void tipc_nmap_add(struct tipc_node_map *nm_ptr, u32 node);
void tipc_nmap_remove(struct tipc_node_map *nm_ptr, u32 node);

/**
 * tipc_nmap_equal - test for equality of node maps
 */
static inline int tipc_nmap_equal(struct tipc_node_map *nm_a, struct tipc_node_map *nm_b)
{
	return !memcmp(nm_a, nm_b, sizeof(*nm_a));
}

void tipc_port_list_add(struct tipc_port_list *pl_ptr, u32 port);
void tipc_port_list_free(struct tipc_port_list *pl_ptr);

void tipc_bclink_init(void);
void tipc_bclink_stop(void);
void tipc_bclink_add_node(u32 addr);
void tipc_bclink_remove_node(u32 addr);
struct tipc_node *tipc_bclink_retransmit_to(void);
void tipc_bclink_acknowledge(struct tipc_node *n_ptr, u32 acked);
int  tipc_bclink_send_msg(struct sk_buff *buf);
void tipc_bclink_recv_pkt(struct sk_buff *buf);
u32  tipc_bclink_get_last_sent(void);
u32  tipc_bclink_acks_missing(struct tipc_node *n_ptr);
void tipc_bclink_update_link_state(struct tipc_node *n_ptr, u32 last_sent);
int  tipc_bclink_stats(char *stats_buf, const u32 buf_size);
int  tipc_bclink_reset_stats(void);
int  tipc_bclink_set_queue_limits(u32 limit);
void tipc_bcbearer_sort(void);

#endif
