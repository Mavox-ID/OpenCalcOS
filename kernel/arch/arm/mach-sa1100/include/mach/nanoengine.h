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
#ifndef __ASM_ARCH_NANOENGINE_H
#define __ASM_ARCH_NANOENGINE_H

#include <mach/irqs.h>

#define GPIO_PC_READY0	11 /* ready for socket 0 (active high)*/
#define GPIO_PC_READY1	12 /* ready for socket 1 (active high) */
#define GPIO_PC_CD0	13 /* detect for socket 0 (active low) */
#define GPIO_PC_CD1	14 /* detect for socket 1 (active low) */
#define GPIO_PC_RESET0	15 /* reset socket 0 */
#define GPIO_PC_RESET1	16 /* reset socket 1 */

#define NANOENGINE_IRQ_GPIO_PCI		IRQ_GPIO0
#define NANOENGINE_IRQ_GPIO_PC_READY0	IRQ_GPIO11
#define NANOENGINE_IRQ_GPIO_PC_READY1	IRQ_GPIO12
#define NANOENGINE_IRQ_GPIO_PC_CD0	IRQ_GPIO13
#define NANOENGINE_IRQ_GPIO_PC_CD1	IRQ_GPIO14

/*
 * nanoEngine Memory Map:
 *
 * 0000.0000 - 003F.0000 -   4 MB Flash
 * C000.0000 - C1FF.FFFF -  32 MB SDRAM
 * 1860.0000 - 186F.FFFF -   1 MB Internal PCI Memory Read/Write
 * 18A1.0000 - 18A1.FFFF -  64 KB Internal PCI Config Space
 * 4000.0000 - 47FF.FFFF - 128 MB External Bus I/O - Multiplexed Mode
 * 4800.0000 - 4FFF.FFFF - 128 MB External Bus I/O - Non-Multiplexed Mode
 *
 */

#define NANO_PCI_MEM_RW_PHYS		0x18600000
#define NANO_PCI_MEM_RW_VIRT		0xf1000000
#define NANO_PCI_MEM_RW_SIZE		SZ_1M
#define NANO_PCI_CONFIG_SPACE_PHYS	0x18A10000
#define NANO_PCI_CONFIG_SPACE_VIRT	0xf2000000
#define NANO_PCI_CONFIG_SPACE_SIZE	SZ_64K

#endif

