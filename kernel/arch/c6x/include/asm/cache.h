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
#ifndef _ASM_C6X_CACHE_H
#define _ASM_C6X_CACHE_H

#include <beep/irqflags.h>

/*
 * Cache line size
 */
#define L1D_CACHE_SHIFT   6
#define L1D_CACHE_BYTES   (1 << L1D_CACHE_SHIFT)

#define L1P_CACHE_SHIFT   5
#define L1P_CACHE_BYTES   (1 << L1P_CACHE_SHIFT)

#define L2_CACHE_SHIFT    7
#define L2_CACHE_BYTES    (1 << L2_CACHE_SHIFT)

/*
 * L2 used as cache
 */
#define L2MODE_SIZE	  L2MODE_256K_CACHE

/*
 * For practical reasons the L1_CACHE_BYTES defines should not be smaller than
 * the L2 line size
 */
#define L1_CACHE_SHIFT        L2_CACHE_SHIFT
#define L1_CACHE_BYTES        (1 << L1_CACHE_SHIFT)

#define L2_CACHE_ALIGN_LOW(x) \
	(((x) & ~(L2_CACHE_BYTES - 1)))
#define L2_CACHE_ALIGN_UP(x) \
	(((x) + (L2_CACHE_BYTES - 1)) & ~(L2_CACHE_BYTES - 1))
#define L2_CACHE_ALIGN_CNT(x) \
	(((x) + (sizeof(int) - 1)) & ~(sizeof(int) - 1))

#define ARCH_DMA_MINALIGN	L1_CACHE_BYTES
#define ARCH_SLAB_MINALIGN	L1_CACHE_BYTES

/*
 * This is the granularity of hardware cacheability control.
 */
#define CACHEABILITY_ALIGN	0x01000000

/*
 * Align a physical address to MAR regions
 */
#define CACHE_REGION_START(v) \
	(((u32) (v)) & ~(CACHEABILITY_ALIGN - 1))
#define CACHE_REGION_END(v) \
	(((u32) (v) + (CACHEABILITY_ALIGN - 1)) & ~(CACHEABILITY_ALIGN - 1))

extern void __init c6x_cache_init(void);

extern void enable_caching(unsigned long start, unsigned long end);
extern void disable_caching(unsigned long start, unsigned long end);

extern void L1_cache_off(void);
extern void L1_cache_on(void);

extern void L1P_cache_global_invalidate(void);
extern void L1D_cache_global_invalidate(void);
extern void L1D_cache_global_writeback(void);
extern void L1D_cache_global_writeback_invalidate(void);
extern void L2_cache_set_mode(unsigned int mode);
extern void L2_cache_global_writeback_invalidate(void);
extern void L2_cache_global_writeback(void);

extern void L1P_cache_block_invalidate(unsigned int start, unsigned int end);
extern void L1D_cache_block_invalidate(unsigned int start, unsigned int end);
extern void L1D_cache_block_writeback_invalidate(unsigned int start,
						 unsigned int end);
extern void L1D_cache_block_writeback(unsigned int start, unsigned int end);
extern void L2_cache_block_invalidate(unsigned int start, unsigned int end);
extern void L2_cache_block_writeback(unsigned int start, unsigned int end);
extern void L2_cache_block_writeback_invalidate(unsigned int start,
						unsigned int end);
extern void L2_cache_block_invalidate_nowait(unsigned int start,
					     unsigned int end);
extern void L2_cache_block_writeback_nowait(unsigned int start,
					    unsigned int end);

extern void L2_cache_block_writeback_invalidate_nowait(unsigned int start,
						       unsigned int end);

#endif /* _ASM_C6X_CACHE_H */
