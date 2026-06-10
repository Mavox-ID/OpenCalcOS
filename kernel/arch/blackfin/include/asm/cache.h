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
#ifndef __ARCH_BLACKFIN_CACHE_H
#define __ARCH_BLACKFIN_CACHE_H

#include <beep/linkage.h>	/* for asmlinkage */

/*
 * Bytes per L1 cache line
 * Blackfin loads 32 bytes for cache
 */
#define L1_CACHE_SHIFT	5
#define L1_CACHE_BYTES	(1 << L1_CACHE_SHIFT)
#define SMP_CACHE_BYTES	L1_CACHE_BYTES

#define ARCH_DMA_MINALIGN	L1_CACHE_BYTES

#ifdef CONFIG_SMP
#define __cacheline_aligned
#else
#define ____cacheline_aligned

/*
 * Put cacheline_aliged data to L1 data memory
 */
#ifdef CONFIG_CACHELINE_ALIGNED_L1
#define __cacheline_aligned				\
	  __attribute__((__aligned__(L1_CACHE_BYTES),	\
		__section__(".data_l1.cacheline_aligned")))
#endif

#endif

/*
 * largest L1 which this arch supports
 */
#define L1_CACHE_SHIFT_MAX	5

#if defined(CONFIG_SMP) && \
    !defined(CONFIG_BFIN_CACHE_COHERENT)
# if defined(CONFIG_BFIN_EXTMEM_ICACHEABLE) || defined(CONFIG_BFIN_L2_ICACHEABLE)
# define __ARCH_SYNC_CORE_ICACHE
# endif
# if defined(CONFIG_BFIN_EXTMEM_DCACHEABLE) || defined(CONFIG_BFIN_L2_DCACHEABLE)
# define __ARCH_SYNC_CORE_DCACHE
# endif
#ifndef __ASSEMBLY__
asmlinkage void __raw_smp_mark_barrier_asm(void);
asmlinkage void __raw_smp_check_barrier_asm(void);

static inline void smp_mark_barrier(void)
{
	__raw_smp_mark_barrier_asm();
}
static inline void smp_check_barrier(void)
{
	__raw_smp_check_barrier_asm();
}

void resync_core_dcache(void);
void resync_core_icache(void);
#endif
#endif


#endif
