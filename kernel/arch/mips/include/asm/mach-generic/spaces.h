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
#ifndef _ASM_MACH_GENERIC_SPACES_H
#define _ASM_MACH_GENERIC_SPACES_H

#include <beep/const.h>

/*
 * This gives the physical RAM offset.
 */
#ifndef PHYS_OFFSET
#define PHYS_OFFSET		_AC(0, UL)
#endif

#ifdef CONFIG_32BIT

#define CAC_BASE		_AC(0x80000000, UL)
#define IO_BASE			_AC(0xa0000000, UL)
#define UNCAC_BASE		_AC(0xa0000000, UL)

#ifndef MAP_BASE
#define MAP_BASE		_AC(0xc0000000, UL)
#endif

/*
 * Memory above this physical address will be considered highmem.
 */
#ifndef HIGHMEM_START
#define HIGHMEM_START		_AC(0x20000000, UL)
#endif

#endif /* CONFIG_32BIT */

#ifdef CONFIG_64BIT

#ifndef CAC_BASE
#ifdef CONFIG_DMA_NONCOHERENT
#define CAC_BASE		_AC(0x9800000000000000, UL)
#else
#define CAC_BASE		_AC(0xa800000000000000, UL)
#endif
#endif

#ifndef IO_BASE
#define IO_BASE			_AC(0x9000000000000000, UL)
#endif

#ifndef UNCAC_BASE
#define UNCAC_BASE		_AC(0x9000000000000000, UL)
#endif

#ifndef MAP_BASE
#define MAP_BASE		_AC(0xc000000000000000, UL)
#endif

/*
 * Memory above this physical address will be considered highmem.
 * Fixme: 59 bits is a fictive number and makes assumptions about processors
 * in the distant future.  Nobody will care for a few years :-)
 */
#ifndef HIGHMEM_START
#define HIGHMEM_START		(_AC(1, UL) << _AC(59, UL))
#endif

#define TO_PHYS(x)		(             ((x) & TO_PHYS_MASK))
#define TO_CAC(x)		(CAC_BASE   | ((x) & TO_PHYS_MASK))
#define TO_UNCAC(x)		(UNCAC_BASE | ((x) & TO_PHYS_MASK))

#endif /* CONFIG_64BIT */

/*
 * This handles the memory map.
 */
#ifndef PAGE_OFFSET
#define PAGE_OFFSET		(CAC_BASE + PHYS_OFFSET)
#endif

#ifndef FIXADDR_TOP
#define FIXADDR_TOP		((unsigned long)(long)(int)0xfffe0000)
#endif

#endif /* __ASM_MACH_GENERIC_SPACES_H */
