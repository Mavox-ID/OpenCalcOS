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
#ifndef _ASM_POSIX_TYPES_H
#define _ASM_POSIX_TYPES_H

#include <asm/sgidefs.h>

/*
 * This file is generally used by user-level software, so you need to
 * be a little careful about namespace pollution etc.  Also, we cannot
 * assume GCC is being used.
 */

typedef long		__kernel_daddr_t;
#define __kernel_daddr_t __kernel_daddr_t

#if (_MIPS_SZLONG == 32)
typedef struct {
	long	val[2];
} __kernel_fsid_t;
#define __kernel_fsid_t __kernel_fsid_t
#endif

#include <asm-generic/posix_types.h>

#endif /* _ASM_POSIX_TYPES_H */
