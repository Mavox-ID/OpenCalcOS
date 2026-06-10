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
#ifndef _ASM_ARCH_HWEIGHT_H
#define _ASM_ARCH_HWEIGHT_H

#ifdef ARCH_HAS_USABLE_BUILTIN_POPCOUNT

#include <asm/types.h>

static inline unsigned int __arch_hweight32(unsigned int w)
{
	return __builtin_popcount(w);
}

static inline unsigned int __arch_hweight16(unsigned int w)
{
	return __builtin_popcount(w & 0xffff);
}

static inline unsigned int __arch_hweight8(unsigned int w)
{
	return __builtin_popcount(w & 0xff);
}

static inline unsigned long __arch_hweight64(__u64 w)
{
	return __builtin_popcountll(w);
}

#else
#include <asm-generic/bitops/arch_hweight.h>
#endif

#endif /* _ASM_ARCH_HWEIGHT_H */
