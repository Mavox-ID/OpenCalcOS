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
#ifndef _ASM_MACH_IP22_SPACES_H
#define _ASM_MACH_IP22_SPACES_H


#ifdef CONFIG_64BIT

#define PAGE_OFFSET		0xffffffff80000000UL

#define CAC_BASE		0xffffffff80000000
#define IO_BASE			0xffffffffa0000000
#define UNCAC_BASE		0xffffffffa0000000
#define MAP_BASE		0xc000000000000000

#endif /* CONFIG_64BIT */

#include <asm/mach-generic/spaces.h>

#endif /* __ASM_MACH_IP22_SPACES_H */
