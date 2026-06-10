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
#ifndef _ASM_IA64_SN_NODEPDA_H
#define _ASM_IA64_SN_NODEPDA_H


#include <asm/irq.h>
#include <asm/sn/arch.h>
#include <asm/sn/intr.h>
#include <asm/sn/bte.h>

/*
 * NUMA Node-Specific Data structures are defined in this file.
 * In particular, this is the location of the node PDA.
 * A pointer to the right node PDA is saved in each CPU PDA.
 */

/*
 * Node-specific data structure.
 *
 * One of these structures is allocated on each node of a NUMA system.
 *
 * This structure provides a convenient way of keeping together 
 * all per-node data structures. 
 */
struct phys_cpuid {
	short			nasid;
	char			subnode;
	char			slice;
};

struct nodepda_s {
	void 		*pdinfo;	/* Platform-dependent per-node info */

	/*
	 * The BTEs on this node are shared by the local cpus
	 */
	struct bteinfo_s	bte_if[MAX_BTES_PER_NODE];	/* Virtual Interface */
	struct timer_list	bte_recovery_timer;
	spinlock_t		bte_recovery_lock;

	/* 
	 * Array of pointers to the nodepdas for each node.
	 */
	struct nodepda_s	*pernode_pdaindr[MAX_COMPACT_NODES]; 

	/*
	 * Array of physical cpu identifiers. Indexed by cpuid.
	 */
	struct phys_cpuid	phys_cpuid[NR_CPUS];
	spinlock_t		ptc_lock ____cacheline_aligned_in_smp;
};

typedef struct nodepda_s nodepda_t;

/*
 * Access Functions for node PDA.
 * Since there is one nodepda for each node, we need a convenient mechanism
 * to access these nodepdas without cluttering code with #ifdefs.
 * The next set of definitions provides this.
 * Routines are expected to use 
 *
 *	sn_nodepda   - to access node PDA for the node on which code is running
 *	NODEPDA(cnodeid)   - to access node PDA for cnodeid
 */

DECLARE_PER_CPU(struct nodepda_s *, __sn_nodepda);
#define sn_nodepda		(__get_cpu_var(__sn_nodepda))
#define	NODEPDA(cnodeid)	(sn_nodepda->pernode_pdaindr[cnodeid])

/*
 * Check if given a compact node id the corresponding node has all the
 * cpus disabled. 
 */
#define is_headless_node(cnodeid)	(nr_cpus_node(cnodeid) == 0)

#endif /* _ASM_IA64_SN_NODEPDA_H */
