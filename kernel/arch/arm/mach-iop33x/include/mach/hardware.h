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
#ifndef __HARDWARE_H
#define __HARDWARE_H

#include <asm/types.h>

/*
 * Note about PCI IO space mappings
 *
 * To make IO space accesses efficient, we store virtual addresses in
 * the IO resources.
 *
 * The PCI IO space is located at virtual 0xfe000000 from physical
 * 0x90000000.  The PCI BARs must be programmed with physical addresses,
 * but when we read them, we convert them to virtual addresses.  See
 * arch/arm/mach-iop3xx/iop3xx-pci.c
 */

#ifndef __ASSEMBLY__
void iop33x_init_irq(void);

extern struct platform_device iop33x_uart0_device;
extern struct platform_device iop33x_uart1_device;
#endif


/*
 * Generic chipset bits
 *
 */
#include "iop33x.h"

/*
 * Board specific bits
 */
#include "iq80331.h"
#include "iq80332.h"


#endif
