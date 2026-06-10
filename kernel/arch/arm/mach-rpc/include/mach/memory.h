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
#ifndef __ASM_ARCH_MEMORY_H
#define __ASM_ARCH_MEMORY_H

/*
 * Physical DRAM offset.
 */
#define PLAT_PHYS_OFFSET	UL(0x10000000)

/*
 * Cache flushing area - ROM
 */
#define FLUSH_BASE_PHYS		0x00000000
#define FLUSH_BASE		0xdf000000

/*
 * Sparsemem support.  Each section is a maximum of 64MB.  The sections
 * are offset by 128MB and can cover 128MB, so that gives us a maximum
 * of 29 physmem bits.
 */
#define MAX_PHYSMEM_BITS	29
#define SECTION_SIZE_BITS	26

#endif
