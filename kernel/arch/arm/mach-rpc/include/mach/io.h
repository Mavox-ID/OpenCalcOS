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
#ifndef __ASM_ARM_ARCH_IO_H
#define __ASM_ARM_ARCH_IO_H

#include <mach/hardware.h>

#define IO_SPACE_LIMIT 0xffff

/*
 * We need PC style IO addressing for:
 *  - floppy (at 0x3f2,0x3f4,0x3f5,0x3f7)
 *  - parport (at 0x278-0x27a, 0x27b-0x27f, 0x778-0x77a)
 *  - 8250 serial (only for compile)
 *
 * These peripherals are found in an area of MMIO which looks very much
 * like an ISA bus, but with registers at the low byte of each word.
 */
#define __io(a)		(PCIO_BASE + ((a) << 2))

#endif
