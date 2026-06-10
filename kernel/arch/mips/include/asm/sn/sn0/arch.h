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
#ifndef _ASM_SN_SN0_ARCH_H
#define _ASM_SN_SN0_ARCH_H


#ifndef SN0XXL  /* 128 cpu SMP max */
/*
 * This is the maximum number of nodes that can be part of a kernel.
 * Effectively, it's the maximum number of compact node ids (cnodeid_t).
 */
#define MAX_COMPACT_NODES       64

/*
 * MAXCPUS refers to the maximum number of CPUs in a single kernel.
 * This is not necessarily the same as MAXNODES * CPUS_PER_NODE
 */
#define MAXCPUS                 128

#else /* SN0XXL system */

#define MAX_COMPACT_NODES       128
#define MAXCPUS                 256

#endif /* SN0XXL */

/*
 * This is the maximum number of NASIDS that can be present in a system.
 * (Highest NASID plus one.)
 */
#define MAX_NASIDS		256

/*
 * MAX_REGIONS refers to the maximum number of hardware partitioned regions.
 */
#define	MAX_REGIONS		64
#define MAX_NONPREMIUM_REGIONS  16
#define MAX_PREMIUM_REGIONS     MAX_REGIONS

/*
 * MAX_PARITIONS refers to the maximum number of logically defined
 * partitions the system can support.
 */
#define MAX_PARTITIONS		MAX_REGIONS

#define NASID_MASK_BYTES	((MAX_NASIDS + 7) / 8)

/*
 * Slot constants for SN0
 */
#ifdef CONFIG_SGI_SN_N_MODE
#define MAX_MEM_SLOTS   16                      /* max slots per node */
#else /* !CONFIG_SGI_SN_N_MODE, assume CONFIG_SGI_SN_M_MODE */
#define MAX_MEM_SLOTS   32                      /* max slots per node */
#endif /* CONFIG_SGI_SN_M_MODE */

#define SLOT_SHIFT      	(27)
#define SLOT_MIN_MEM_SIZE	(32*1024*1024)

#define CPUS_PER_NODE		2	/* CPUs on a single hub */
#define CPUS_PER_NODE_SHFT	1	/* Bits to shift in the node number */
#define CPUS_PER_SUBNODE	2	/* CPUs on a single hub PI */

#endif /* _ASM_SN_SN0_ARCH_H */
