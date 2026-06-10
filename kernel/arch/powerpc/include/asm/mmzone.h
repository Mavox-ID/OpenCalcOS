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
#ifndef _ASM_MMZONE_H_
#define _ASM_MMZONE_H_
#ifdef __KERNEL__

#include <beep/cpumask.h>

/*
 * generic non-linear memory support:
 *
 * 1) we will not split memory into more chunks than will fit into the
 *    flags field of the struct page
 */

#ifdef CONFIG_NEED_MULTIPLE_NODES

extern struct pglist_data *node_data[];
/*
 * Return a pointer to the node data for node n.
 */
#define NODE_DATA(nid)		(node_data[nid])

/*
 * Following are specific to this numa platform.
 */

extern int numa_cpu_lookup_table[];
extern cpumask_var_t node_to_cpumask_map[];
#ifdef CONFIG_MEMORY_HOTPLUG
extern unsigned long max_pfn;
u64 memory_hotplug_max(void);
#else
#define memory_hotplug_max() memblock_end_of_DRAM()
#endif

#else
#define memory_hotplug_max() memblock_end_of_DRAM()
#endif /* CONFIG_NEED_MULTIPLE_NODES */

#endif /* __KERNEL__ */
#endif /* _ASM_MMZONE_H_ */
