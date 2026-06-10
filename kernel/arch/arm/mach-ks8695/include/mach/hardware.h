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

#include <asm/sizes.h>

/*
 * Clocks are derived from MCLK, which is 25Mhz
 */
#define KS8695_CLOCK_RATE	25000000

/*
 * Physical RAM address.
 */
#define KS8695_SDRAM_PA		0x00000000


/*
 * We map an entire MiB with the System Configuration Registers in even
 * though only 64KiB is needed. This makes it easier for use with the
 * head debug code as the initial MMU setup only deals in L1 sections.
 */
#define KS8695_IO_PA		0x03F00000
#define KS8695_IO_VA		IOMEM(0xF0000000)
#define KS8695_IO_SIZE		SZ_1M

#define KS8695_PCIMEM_PA	0x60000000
#define KS8695_PCIMEM_SIZE	SZ_512M

#define KS8695_PCIIO_PA		0x80000000
#define KS8695_PCIIO_SIZE	SZ_64K

#endif
