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
#ifndef __ASM_SH_BL_BIT_64_H
#define __ASM_SH_BL_BIT_64_H

#include <asm/processor.h>

#define SR_BL_LL	0x0000000010000000LL

static inline void set_bl_bit(void)
{
	unsigned long long __dummy0, __dummy1 = SR_BL_LL;

	__asm__ __volatile__("getcon	" __SR ", %0\n\t"
			     "or	%0, %1, %0\n\t"
			     "putcon	%0, " __SR "\n\t"
			     : "=&r" (__dummy0)
			     : "r" (__dummy1));

}

static inline void clear_bl_bit(void)
{
	unsigned long long __dummy0, __dummy1 = ~SR_BL_LL;

	__asm__ __volatile__("getcon	" __SR ", %0\n\t"
			     "and	%0, %1, %0\n\t"
			     "putcon	%0, " __SR "\n\t"
			     : "=&r" (__dummy0)
			     : "r" (__dummy1));
}

#endif /* __ASM_SH_BL_BIT_64_H */
