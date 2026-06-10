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
#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H

/*
 * Start of virtual addresses for IO devices
 */
#define IO_BASE		0xF0000000

/*
 * This macro relies on fact that for all HW i/o addresses bits 20-23 are 0
 */
#define IO_ADDRESS(x)	IOMEM(((((x) & 0xff000000) >> 4) | ((x) & 0xfffff)) |\
			 IO_BASE)

#define io_p2v(x)	((void __iomem *) (unsigned long) IO_ADDRESS(x))
#define io_v2p(x)	((((x) & 0x0ff00000) << 4) | ((x) & 0x000fffff))

#endif
