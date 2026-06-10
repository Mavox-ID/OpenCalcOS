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
#ifndef _ASM_C6X_SWAB_H
#define _ASM_C6X_SWAB_H

static inline __attribute_const__ __u16 __c6x_swab16(__u16 val)
{
	asm("swap4 .l1 %0,%0\n" : "+a"(val));
	return val;
}

static inline __attribute_const__ __u32 __c6x_swab32(__u32 val)
{
	asm("swap4 .l1 %0,%0\n"
	    "swap2 .l1 %0,%0\n"
	    : "+a"(val));
	return val;
}

static inline __attribute_const__ __u64 __c6x_swab64(__u64 val)
{
	asm("   swap2 .s1 %p0,%P0\n"
	    "|| swap2 .l1 %P0,%p0\n"
	    "   swap4 .l1 %p0,%p0\n"
	    "   swap4 .l1 %P0,%P0\n"
	    : "+a"(val));
	return val;
}

static inline __attribute_const__ __u32 __c6x_swahw32(__u32 val)
{
	asm("swap2 .l1 %0,%0\n" : "+a"(val));
	return val;
}

static inline __attribute_const__ __u32 __c6x_swahb32(__u32 val)
{
	asm("swap4 .l1 %0,%0\n" : "+a"(val));
	return val;
}

#define __arch_swab16 __c6x_swab16
#define __arch_swab32 __c6x_swab32
#define __arch_swab64 __c6x_swab64
#define __arch_swahw32 __c6x_swahw32
#define __arch_swahb32 __c6x_swahb32

#endif /* _ASM_C6X_SWAB_H */
