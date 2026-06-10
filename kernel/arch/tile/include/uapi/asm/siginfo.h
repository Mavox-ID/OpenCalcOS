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
#ifndef _ASM_TILE_SIGINFO_H
#define _ASM_TILE_SIGINFO_H

#define __ARCH_SI_TRAPNO

#ifdef __LP64__
# define __ARCH_SI_PREAMBLE_SIZE	(4 * sizeof(int))
#endif

#include <asm-generic/siginfo.h>

/*
 * Additional Tile-specific SIGILL si_codes
 */
#define ILL_DBLFLT	(__SI_FAULT|9)	/* double fault */
#define ILL_HARDWALL	(__SI_FAULT|10)	/* user networks hardwall violation */
#undef NSIGILL
#define NSIGILL		10

#endif /* _ASM_TILE_SIGINFO_H */
