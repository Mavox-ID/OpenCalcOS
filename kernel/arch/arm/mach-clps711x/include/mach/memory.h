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
#define PLAT_PHYS_OFFSET	UL(0xc0000000)

/*
 * The PS7211 allows up to 256MB max per DRAM bank, but the EDB7211
 * uses only one of the two banks (bank #1).  However, even within
 * bank #1, memory is discontiguous.
 *
 * The EDB7211 has two 8MB DRAM areas with 8MB of empty space between
 * them, so we use 24 for the node max shift to get 16MB node sizes.
 */

#define SECTION_SIZE_BITS	24
#define MAX_PHYSMEM_BITS	32

#endif

