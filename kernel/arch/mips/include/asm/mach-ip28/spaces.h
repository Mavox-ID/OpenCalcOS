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
#ifndef _ASM_MACH_IP28_SPACES_H
#define _ASM_MACH_IP28_SPACES_H

#define CAC_BASE		0xa800000000000000

#define HIGHMEM_START		(~0UL)

#define PHYS_OFFSET		_AC(0x20000000, UL)

#include <asm/mach-generic/spaces.h>

#endif /* _ASM_MACH_IP28_SPACES_H */
