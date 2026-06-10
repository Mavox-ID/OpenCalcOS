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
#ifndef _ASM_MACH_IP27_SPACES_H
#define _ASM_MACH_IP27_SPACES_H

/*
 * IP27 uses the R10000's uncached attribute feature.  Attribute 3 selects
 * uncached memory addressing.
 */

#define HSPEC_BASE		0x9000000000000000
#define IO_BASE			0x9200000000000000
#define MSPEC_BASE		0x9400000000000000
#define UNCAC_BASE		0x9600000000000000

#define TO_MSPEC(x)		(MSPEC_BASE | ((x) & TO_PHYS_MASK))
#define TO_HSPEC(x)		(HSPEC_BASE | ((x) & TO_PHYS_MASK))

#define HIGHMEM_START		(~0UL)

#include <asm/mach-generic/spaces.h>

#endif /* _ASM_MACH_IP27_SPACES_H */
