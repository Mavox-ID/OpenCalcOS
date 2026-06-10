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
#ifndef _XTENSA_SWAB_H
#define _XTENSA_SWAB_H

#include <beep/types.h>
#include <beep/compiler.h>

#define __SWAB_64_THRU_32__

static inline __attribute_const__ __u32 __arch_swab32(__u32 x)
{
    __u32 res;
    /* instruction sequence from Xtensa ISA release 2/2000 */
    __asm__("ssai     8           \n\t"
	    "srli     %0, %1, 16  \n\t"
	    "src      %0, %0, %1  \n\t"
	    "src      %0, %0, %0  \n\t"
	    "src      %0, %1, %0  \n"
	    : "=&a" (res)
	    : "a" (x)
	    );
    return res;
}
#define __arch_swab32 __arch_swab32

static inline __attribute_const__ __u16 __arch_swab16(__u16 x)
{
    /* Given that 'short' values are signed (i.e., can be negative),
     * we cannot assume that the upper 16-bits of the register are
     * zero.  We are careful to mask values after shifting.
     */

    /* There exists an anomaly between xt-gcc and xt-xcc.  xt-gcc
     * inserts an extui instruction after putting this function inline
     * to ensure that it uses only the least-significant 16 bits of
     * the result.  xt-xcc doesn't use an extui, but assumes the
     * __asm__ macro follows convention that the upper 16 bits of an
     * 'unsigned short' result are still zero.  This macro doesn't
     * follow convention; indeed, it leaves garbage in the upport 16
     * bits of the register.

     * Declaring the temporary variables 'res' and 'tmp' to be 32-bit
     * types while the return type of the function is a 16-bit type
     * forces both compilers to insert exactly one extui instruction
     * (or equivalent) to mask off the upper 16 bits. */

    __u32 res;
    __u32 tmp;

    __asm__("extui    %1, %2, 8, 8\n\t"
	    "slli     %0, %2, 8   \n\t"
	    "or       %0, %0, %1  \n"
	    : "=&a" (res), "=&a" (tmp)
	    : "a" (x)
	    );

    return res;
}
#define __arch_swab16 __arch_swab16

#endif /* _XTENSA_SWAB_H */
