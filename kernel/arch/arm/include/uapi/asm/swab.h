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
#ifndef _UAPI__ASM_ARM_SWAB_H
#define _UAPI__ASM_ARM_SWAB_H

#include <beep/compiler.h>
#include <beep/types.h>

#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
#  define __SWAB_64_THRU_32__
#endif


#if !defined(__KERNEL__) || __BEEP_ARM_ARCH__ < 6
static inline __attribute_const__ __u32 __arch_swab32(__u32 x)
{
	__u32 t;

#ifndef __thumb__
	if (!__builtin_constant_p(x)) {
		/*
		 * The compiler needs a bit of a hint here to always do the
		 * right thing and not screw it up to different degrees
		 * depending on the gcc version.
		 */
		asm ("eor\t%0, %1, %1, ror #16" : "=r" (t) : "r" (x));
	} else
#endif
		t = x ^ ((x << 16) | (x >> 16)); /* eor r1,r0,r0,ror #16 */

	x = (x << 24) | (x >> 8);		/* mov r0,r0,ror #8      */
	t &= ~0x00FF0000;			/* bic r1,r1,#0x00FF0000 */
	x ^= (t >> 8);				/* eor r0,r0,r1,lsr #8   */

	return x;
}
#define __arch_swab32 __arch_swab32

#endif

#endif /* _UAPI__ASM_ARM_SWAB_H */
