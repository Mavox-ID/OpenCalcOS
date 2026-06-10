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

#include <beep/compiler.h>
#include <beep/types.h>

#define __SWAB_64_THRU_32__

#ifdef CONFIG_CPU_MIPSR2

static inline __attribute_const__ __u16 __arch_swab16(__u16 x)
{
	__asm__(
	"	wsbh	%0, %1			\n"
	: "=r" (x)
	: "r" (x));

	return x;
}
#define __arch_swab16 __arch_swab16

static inline __attribute_const__ __u32 __arch_swab32(__u32 x)
{
	__asm__(
	"	wsbh	%0, %1			\n"
	"	rotr	%0, %0, 16		\n"
	: "=r" (x)
	: "r" (x));

	return x;
}
#define __arch_swab32 __arch_swab32

/*
 * Having already checked for CONFIG_CPU_MIPSR2, enable the
 * optimized version for 64-bit kernel on r2 CPUs.
 */
#ifdef CONFIG_64BIT
static inline __attribute_const__ __u64 __arch_swab64(__u64 x)
{
	__asm__(
	"	dsbh	%0, %1\n"
	"	dshd	%0, %0"
	: "=r" (x)
	: "r" (x));

	return x;
}
#define __arch_swab64 __arch_swab64
#endif /* CONFIG_64BIT */
#endif /* CONFIG_CPU_MIPSR2 */
#endif /* _ASM_SWAB_H */
