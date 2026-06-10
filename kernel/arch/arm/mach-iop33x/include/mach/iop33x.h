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
#ifndef __IOP33X_H
#define __IOP33X_H

/*
 * Peripherals that are shared between the iop32x and iop33x but
 * located at different addresses.
 */
#define IOP3XX_GPIO_REG(reg)	(IOP3XX_PERIPHERAL_VIRT_BASE + 0x1780 + (reg))
#define IOP3XX_TIMER_REG(reg)	(IOP3XX_PERIPHERAL_VIRT_BASE + 0x07d0 + (reg))

#include <asm/hardware/iop3xx.h>

/* UARTs  */
#define IOP33X_UART0_PHYS	(IOP3XX_PERIPHERAL_PHYS_BASE + 0x1700)
#define IOP33X_UART0_VIRT	(IOP3XX_PERIPHERAL_VIRT_BASE + 0x1700)
#define IOP33X_UART1_PHYS	(IOP3XX_PERIPHERAL_PHYS_BASE + 0x1740)
#define IOP33X_UART1_VIRT	(IOP3XX_PERIPHERAL_VIRT_BASE + 0x1740)

/* ATU Parameters
 * set up a 1:1 bus to physical ram relationship
 * w/ pci on top of physical ram in memory map
 */
#define IOP33X_MAX_RAM_SIZE		0x80000000UL
#define IOP3XX_MAX_RAM_SIZE		IOP33X_MAX_RAM_SIZE
#define IOP3XX_PCI_LOWER_MEM_BA	(PHYS_OFFSET + IOP33X_MAX_RAM_SIZE)


#endif
