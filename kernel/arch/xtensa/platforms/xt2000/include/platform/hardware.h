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
/*
 * This file contains the hardware configuration of the XT2000 board.
 */

#ifndef _XTENSA_XT2000_HARDWARE_H
#define _XTENSA_XT2000_HARDWARE_H

#include <variant/core.h>

/* 
 * Memory configuration.
 */

#define PLATFORM_DEFAULT_MEM_START 0x00000000
#define PLATFORM_DEFAULT_MEM_SIZE 0x08000000

/*
 * Number of platform IRQs
 */
#define PLATFORM_NR_IRQS 3
/*
 * On-board components.
 */

#define SONIC83934_INTNUM	XCHAL_EXTINT3_NUM
#define SONIC83934_ADDR		IOADDR(0x0d030000)

/*
 * V3-PCI
 */

/* The XT2000 uses the V3 as a cascaded interrupt controller for the PCI bus */

#define IRQ_PCI_A		(XCHAL_NUM_INTERRUPTS + 0)
#define IRQ_PCI_B		(XCHAL_NUM_INTERRUPTS + 1)
#define IRQ_PCI_C		(XCHAL_NUM_INTERRUPTS + 2)

/*
 * Various other components.
 */

#define XT2000_LED_ADDR		IOADDR(0x0d040000)

#endif /* _XTENSA_XT2000_HARDWARE_H */
