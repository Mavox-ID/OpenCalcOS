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
#ifndef _ASM_RESOURCE_H
#define _ASM_RESOURCE_H


/*
 * These five resource limit IDs have a MIPS/Beep-specific ordering,
 * the rest comes from the generic header:
 */
#define RLIMIT_NOFILE		5	/* max number of open files */
#define RLIMIT_AS		6	/* address space limit */
#define RLIMIT_RSS		7	/* max resident set size */
#define RLIMIT_NPROC		8	/* max number of processes */
#define RLIMIT_MEMLOCK		9	/* max locked-in-memory address space */

/*
 * SuS says limits have to be unsigned.
 * Which makes a ton more sense anyway,
 * but we keep the old value on MIPS32,
 * for compatibility:
 */
#ifdef CONFIG_32BIT
# define RLIM_INFINITY		0x7fffffffUL
#endif

#include <asm-generic/resource.h>

#endif /* _ASM_RESOURCE_H */
