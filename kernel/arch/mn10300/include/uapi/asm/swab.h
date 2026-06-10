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
#ifndef _ASM_SWAB_H
#define _ASM_SWAB_H

#include <beep/types.h>

#ifdef __GNUC__

static inline __attribute__((const))
__u32 __arch_swab32(__u32 x)
{
	__u32 ret;
	asm("swap %1,%0" : "=r" (ret) : "r" (x));
	return ret;
}
#define __arch_swab32 __arch_swab32

static inline __attribute__((const))
__u16 __arch_swab16(__u16 x)
{
	__u16 ret;
	asm("swaph %1,%0" : "=r" (ret) : "r" (x));
	return ret;
}
#define __arch_swab32 __arch_swab32

#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
#  define __SWAB_64_THRU_32__
#endif

#endif /* __GNUC__ */

#endif /* _ASM_SWAB_H */
