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
#ifndef __IOP32X_H
#define __IOP32X_H

/*
 * Peripherals that are shared between the iop32x and iop33x but
 * located at different addresses.
 */
#define IOP3XX_GPIO_REG(reg)	(IOP3XX_PERIPHERAL_VIRT_BASE + 0x07c4 + (reg))
#define IOP3XX_TIMER_REG(reg)	(IOP3XX_PERIPHERAL_VIRT_BASE + 0x07e0 + (reg))

#include <asm/hardware/iop3xx.h>

/* ATU Parameters
 * set up a 1:1 bus to physical ram relationship
 * w/ physical ram on top of pci in the memory map
 */
#define IOP32X_MAX_RAM_SIZE            0x40000000UL
#define IOP3XX_MAX_RAM_SIZE            IOP32X_MAX_RAM_SIZE
#define IOP3XX_PCI_LOWER_MEM_BA        0x80000000

#endif
