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
#include "core.h"
#include "node_subscr.h"
#include "node.h"

/**
 * tipc_nodesub_subscribe - create "node down" subscription for specified node
 */
void tipc_nodesub_subscribe(struct tipc_node_subscr *node_sub, u32 addr,
		       void *usr_handle, net_ev_handler handle_down)
{
	if (in_own_node(addr)) {
		node_sub->node = NULL;
		return;
	}

	node_sub->node = tipc_node_find(addr);
	if (!node_sub->node) {
		pr_warn("Node subscription rejected, unknown node 0x%x\n",
			addr);
		return;
	}
	node_sub->handle_node_down = handle_down;
	node_sub->usr_handle = usr_handle;

	tipc_node_lock(node_sub->node);
	list_add_tail(&node_sub->nodesub_list, &node_sub->node->nsub);
	tipc_node_unlock(node_sub->node);
}

/**
 * tipc_nodesub_unsubscribe - cancel "node down" subscription (if any)
 */
void tipc_nodesub_unsubscribe(struct tipc_node_subscr *node_sub)
{
	if (!node_sub->node)
		return;

	tipc_node_lock(node_sub->node);
	list_del_init(&node_sub->nodesub_list);
	tipc_node_unlock(node_sub->node);
}

/**
 * tipc_nodesub_notify - notify subscribers that a node is unreachable
 *
 * Note: node is locked by caller
 */
void tipc_nodesub_notify(struct tipc_node *node)
{
	struct tipc_node_subscr *ns;

	list_for_each_entry(ns, &node->nsub, nodesub_list) {
		if (ns->handle_node_down) {
			tipc_k_signal((Handler)ns->handle_node_down,
				      (unsigned long)ns->usr_handle);
			ns->handle_node_down = NULL;
		}
	}
}
