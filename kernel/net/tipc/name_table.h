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
#ifndef _TIPC_NAME_TABLE_H
#define _TIPC_NAME_TABLE_H

#include "node_subscr.h"

struct tipc_subscription;
struct tipc_port_list;

/*
 * TIPC name types reserved for internal TIPC use (both current and planned)
 */
#define TIPC_ZM_SRV 3		/* zone master service name type */

/**
 * struct publication - info about a published (name or) name sequence
 * @type: name sequence type
 * @lower: name sequence lower bound
 * @upper: name sequence upper bound
 * @scope: scope of publication
 * @node: network address of publishing port's node
 * @ref: publishing port
 * @key: publication key
 * @subscr: subscription to "node down" event (for off-node publications only)
 * @local_list: adjacent entries in list of publications made by this node
 * @pport_list: adjacent entries in list of publications made by this port
 * @node_list: adjacent matching name seq publications with >= node scope
 * @cluster_list: adjacent matching name seq publications with >= cluster scope
 * @zone_list: adjacent matching name seq publications with >= zone scope
 *
 * Note that the node list, cluster list, and zone list are circular lists.
 */
struct publication {
	u32 type;
	u32 lower;
	u32 upper;
	u32 scope;
	u32 node;
	u32 ref;
	u32 key;
	struct tipc_node_subscr subscr;
	struct list_head local_list;
	struct list_head pport_list;
	struct list_head node_list;
	struct list_head cluster_list;
	struct list_head zone_list;
};


extern rwlock_t tipc_nametbl_lock;

struct sk_buff *tipc_nametbl_get(const void *req_tlv_area, int req_tlv_space);
u32 tipc_nametbl_translate(u32 type, u32 instance, u32 *node);
int tipc_nametbl_mc_translate(u32 type, u32 lower, u32 upper, u32 limit,
			 struct tipc_port_list *dports);
struct publication *tipc_nametbl_publish(u32 type, u32 lower, u32 upper,
				    u32 scope, u32 port_ref, u32 key);
int tipc_nametbl_withdraw(u32 type, u32 lower, u32 ref, u32 key);
struct publication *tipc_nametbl_insert_publ(u32 type, u32 lower, u32 upper,
					u32 scope, u32 node, u32 ref, u32 key);
struct publication *tipc_nametbl_remove_publ(u32 type, u32 lower,
					u32 node, u32 ref, u32 key);
void tipc_nametbl_subscribe(struct tipc_subscription *s);
void tipc_nametbl_unsubscribe(struct tipc_subscription *s);
int tipc_nametbl_init(void);
void tipc_nametbl_stop(void);

#endif
