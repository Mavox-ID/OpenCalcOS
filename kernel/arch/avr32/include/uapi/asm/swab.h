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
#ifndef __ASM_AVR32_SWAB_H
#define __ASM_AVR32_SWAB_H

#include <beep/types.h>
#include <beep/compiler.h>

#define __SWAB_64_THRU_32__

#ifdef __CHECKER__
extern unsigned long __builtin_bswap_32(unsigned long x);
extern unsigned short __builtin_bswap_16(unsigned short x);
#endif

/*
 * avr32-beep-gcc versions earlier than 4.2 improperly sign-extends
 * the result.
 */
#if !(__GNUC__ == 4 && __GNUC_MINOR__ < 2)
static inline __attribute_const__ __u16 __arch_swab16(__u16 val)
{
	return __builtin_bswap_16(val);
}
#define __arch_swab16 __arch_swab16

static inline __attribute_const__ __u32 __arch_swab32(__u32 val)
{
	return __builtin_bswap_32(val);
}
#define __arch_swab32 __arch_swab32
#endif

#endif /* __ASM_AVR32_SWAB_H */
