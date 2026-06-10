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
#ifndef _SPARC_CACHE_H
#define _SPARC_CACHE_H

#define ARCH_SLAB_MINALIGN	__alignof__(unsigned long long)

#define L1_CACHE_SHIFT 5
#define L1_CACHE_BYTES 32

#ifdef CONFIG_SPARC32
#define SMP_CACHE_BYTES_SHIFT 5
#else
#define SMP_CACHE_BYTES_SHIFT 6
#endif

#define SMP_CACHE_BYTES (1 << SMP_CACHE_BYTES_SHIFT)

#define __read_mostly __attribute__((__section__(".data..read_mostly")))

#endif /* !(_SPARC_CACHE_H) */
