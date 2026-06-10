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
#ifndef __UNICORE_BITOPS_H__
#define __UNICORE_BITOPS_H__

#define _ASM_GENERIC_BITOPS_FLS_H_
#define _ASM_GENERIC_BITOPS___FLS_H_
#define _ASM_GENERIC_BITOPS_FFS_H_
#define _ASM_GENERIC_BITOPS___FFS_H_
/*
 * On UNICORE, those functions can be implemented around
 * the cntlz instruction for much better code efficiency.
 */

static inline int fls(int x)
{
	int ret;

	asm("cntlz\t%0, %1" : "=r" (ret) : "r" (x) : "cc");
	ret = 32 - ret;

	return ret;
}

#define __fls(x) (fls(x) - 1)
#define ffs(x) ({ unsigned long __t = (x); fls(__t & -__t); })
#define __ffs(x) (ffs(x) - 1)

#include <asm-generic/bitops.h>

/* following definitions: to avoid using codes in lib/find_*.c */
#define find_next_bit		find_next_bit
#define find_next_zero_bit	find_next_zero_bit
#define find_first_bit		find_first_bit
#define find_first_zero_bit	find_first_zero_bit

#endif /* __UNICORE_BITOPS_H__ */
