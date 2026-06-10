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

#define PLAT_PHYS_OFFSET		UL(0x20000000)

/*
 * Sparsemem support
 * Physical memory can be located from 0x20000000 to 0x7fffffff,
 * so MAX_PHYSMEM_BITS is 31.
 */

#define MAX_PHYSMEM_BITS	31
#define SECTION_SIZE_BITS	28

#endif /* __ASM_ARCH_MEMORY_H */
