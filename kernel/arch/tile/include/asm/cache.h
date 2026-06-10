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
#ifndef _ASM_TILE_CACHE_H
#define _ASM_TILE_CACHE_H

#include <arch/chip.h>

/* bytes per L1 data cache line */
#define L1_CACHE_SHIFT		CHIP_L1D_LOG_LINE_SIZE()
#define L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

/* bytes per L2 cache line */
#define L2_CACHE_SHIFT		CHIP_L2_LOG_LINE_SIZE()
#define L2_CACHE_BYTES		(1 << L2_CACHE_SHIFT)
#define L2_CACHE_ALIGN(x)	(((x)+(L2_CACHE_BYTES-1)) & -L2_CACHE_BYTES)

/*
 * TILEPro I/O is not always coherent (networking typically uses coherent
 * I/O, but PCI traffic does not) and setting ARCH_DMA_MINALIGN to the
 * L2 cacheline size helps ensure that kernel heap allocations are aligned.
 * TILE-Gx I/O is always coherent when used on hash-for-home pages.
 *
 * However, it's possible at runtime to request not to use hash-for-home
 * for the kernel heap, in which case the kernel will use flush-and-inval
 * to manage coherence.  As a result, we use L2_CACHE_BYTES for the
 * DMA minimum alignment to avoid false sharing in the kernel heap.
 */
#define ARCH_DMA_MINALIGN	L2_CACHE_BYTES

/* use the cache line size for the L2, which is where it counts */
#define SMP_CACHE_BYTES_SHIFT	L2_CACHE_SHIFT
#define SMP_CACHE_BYTES		L2_CACHE_BYTES
#define INTERNODE_CACHE_SHIFT   L2_CACHE_SHIFT
#define INTERNODE_CACHE_BYTES   L2_CACHE_BYTES

/* Group together read-mostly things to avoid cache false sharing */
#define __read_mostly __attribute__((__section__(".data..read_mostly")))

/*
 * Attribute for data that is kept read/write coherent until the end of
 * initialization, then bumped to read/only incoherent for performance.
 */
#define __write_once __attribute__((__section__(".w1data")))

#endif /* _ASM_TILE_CACHE_H */
