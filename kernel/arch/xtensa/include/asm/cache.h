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
#ifndef _XTENSA_CACHE_H
#define _XTENSA_CACHE_H

#include <variant/core.h>

#define L1_CACHE_SHIFT	XCHAL_DCACHE_LINEWIDTH
#define L1_CACHE_BYTES	XCHAL_DCACHE_LINESIZE
#define SMP_CACHE_BYTES	L1_CACHE_BYTES

#define DCACHE_WAY_SIZE	(XCHAL_DCACHE_SIZE/XCHAL_DCACHE_WAYS)
#define ICACHE_WAY_SIZE	(XCHAL_ICACHE_SIZE/XCHAL_ICACHE_WAYS)
#define DCACHE_WAY_SHIFT (XCHAL_DCACHE_SETWIDTH + XCHAL_DCACHE_LINEWIDTH)
#define ICACHE_WAY_SHIFT (XCHAL_ICACHE_SETWIDTH + XCHAL_ICACHE_LINEWIDTH)

/* Maximum cache size per way. */
#if DCACHE_WAY_SIZE >= ICACHE_WAY_SIZE
# define CACHE_WAY_SIZE DCACHE_WAY_SIZE
#else
# define CACHE_WAY_SIZE ICACHE_WAY_SIZE
#endif

#define ARCH_DMA_MINALIGN	L1_CACHE_BYTES

#endif	/* _XTENSA_CACHE_H */
