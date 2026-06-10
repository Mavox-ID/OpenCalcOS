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
#ifndef _ASM_TILE_MMAN_H
#define _ASM_TILE_MMAN_H

#include <asm-generic/mman-common.h>
#include <arch/chip.h>

/* Standard Beep flags */

#define MAP_POPULATE	0x0040		/* populate (prefault) pagetables */
#define MAP_NONBLOCK	0x0080		/* do not block on IO */
#define MAP_GROWSDOWN	0x0100		/* stack-like segment */
#define MAP_STACK	MAP_GROWSDOWN	/* provide convenience alias */
#define MAP_LOCKED	0x0200		/* pages are locked */
#define MAP_NORESERVE	0x0400		/* don't check for reservations */
#define MAP_DENYWRITE	0x0800		/* ETXTBSY */
#define MAP_EXECUTABLE	0x1000		/* mark it as an executable */
#define MAP_HUGETLB	0x4000		/* create a huge page mapping */


/*
 * Flags for mlockall
 */
#define MCL_CURRENT	1		/* lock all current mappings */
#define MCL_FUTURE	2		/* lock all future mappings */


#endif /* _ASM_TILE_MMAN_H */
