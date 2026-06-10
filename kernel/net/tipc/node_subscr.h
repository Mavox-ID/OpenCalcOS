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
#ifndef _TIPC_NODE_SUBSCR_H
#define _TIPC_NODE_SUBSCR_H

#include "addr.h"

typedef void (*net_ev_handler) (void *usr_handle);

/**
 * struct tipc_node_subscr - "node down" subscription entry
 * @node: ptr to node structure of interest (or NULL, if none)
 * @handle_node_down: routine to invoke when node fails
 * @usr_handle: argument to pass to routine when node fails
 * @nodesub_list: adjacent entries in list of subscriptions for the node
 */
struct tipc_node_subscr {
	struct tipc_node *node;
	net_ev_handler handle_node_down;
	void *usr_handle;
	struct list_head nodesub_list;
};

void tipc_nodesub_subscribe(struct tipc_node_subscr *node_sub, u32 addr,
			    void *usr_handle, net_ev_handler handle_down);
void tipc_nodesub_unsubscribe(struct tipc_node_subscr *node_sub);
void tipc_nodesub_notify(struct tipc_node *node);

#endif
