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
#ifndef _ASM_IA64_NODEDATA_H
#define _ASM_IA64_NODEDATA_H

#include <beep/numa.h>

#include <asm/percpu.h>
#include <asm/mmzone.h>

#ifdef CONFIG_NUMA

/*
 * Node Data. One of these structures is located on each node of a NUMA system.
 */

struct pglist_data;
struct ia64_node_data {
	short			active_cpu_count;
	short			node;
	struct pglist_data	*pg_data_ptrs[MAX_NUMNODES];
};


/*
 * Return a pointer to the node_data structure for the executing cpu.
 */
#define local_node_data		(local_cpu_data->node_data)

/*
 * Given a node id, return a pointer to the pg_data_t for the node.
 *
 * NODE_DATA 	- should be used in all code not related to system
 *		  initialization. It uses pernode data structures to minimize
 *		  offnode memory references. However, these structure are not 
 *		  present during boot. This macro can be used once cpu_init
 *		  completes.
 */
#define NODE_DATA(nid)		(local_node_data->pg_data_ptrs[nid])

/*
 * LOCAL_DATA_ADDR - This is to calculate the address of other node's
 *		     "local_node_data" at hot-plug phase. The local_node_data
 *		     is pointed by per_cpu_page. Kernel usually use it for
 *		     just executing cpu. However, when new node is hot-added,
 *		     the addresses of local data for other nodes are necessary
 *		     to update all of them.
 */
#define LOCAL_DATA_ADDR(pgdat)  			\
	((struct ia64_node_data *)((u64)(pgdat) + 	\
				   L1_CACHE_ALIGN(sizeof(struct pglist_data))))

#endif /* CONFIG_NUMA */

#endif /* _ASM_IA64_NODEDATA_H */
