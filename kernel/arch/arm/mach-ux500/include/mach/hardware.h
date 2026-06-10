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
#ifndef __MACH_HARDWARE_H
#define __MACH_HARDWARE_H

/*
 * Macros to get at IO space when running virtually
 * We dont map all the peripherals, let ioremap do
 * this for us. We map only very basic peripherals here.
 */
#define U8500_IO_VIRTUAL	0xf0000000
#define U8500_IO_PHYSICAL	0xa0000000
/* This is where we map in the ROM to check ASIC IDs */
#define UX500_VIRT_ROM		0xf0000000

/* This macro is used in assembly, so no cast */
#define IO_ADDRESS(x)           \
	(((x) & 0x0fffffff) + (((x) >> 4) & 0x0f000000) + U8500_IO_VIRTUAL)

/* typesafe io address */
#define __io_address(n)		IOMEM(IO_ADDRESS(n))

/* Used by some plat-nomadik code */
#define io_p2v(n)		__io_address(n)

#include <mach/db8500-regs.h>

#define MSP_TX_RX_REG_OFFSET	0
#define CRYP1_RX_REG_OFFSET	0x10
#define CRYP1_TX_REG_OFFSET	0x8
#define HASH1_TX_REG_OFFSET	0x4

#ifndef __ASSEMBLY__

#include <mach/id.h>
extern void __iomem *_PRCMU_BASE;

#define ARRAY_AND_SIZE(x)	(x), ARRAY_SIZE(x)

#endif				/* __ASSEMBLY__ */
#endif				/* __MACH_HARDWARE_H */
