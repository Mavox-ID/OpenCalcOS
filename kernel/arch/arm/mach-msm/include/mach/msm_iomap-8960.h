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
#ifndef __ASM_ARCH_MSM_IOMAP_8960_H
#define __ASM_ARCH_MSM_IOMAP_8960_H

/* Physical base address and size of peripherals.
 * Ordered by the virtual base addresses they will be mapped at.
 *
 * If you add or remove entries here, you'll want to edit the
 * msm_io_desc array in arch/arm/mach-msm/io.c to reflect your
 * changes.
 *
 */


#define MSM8960_QGIC_DIST_PHYS	0x02000000
#define MSM8960_QGIC_DIST_SIZE	SZ_4K

#define MSM8960_QGIC_CPU_PHYS	0x02002000
#define MSM8960_QGIC_CPU_SIZE	SZ_4K

#define MSM8960_TMR_PHYS	0x0200A000
#define MSM8960_TMR_SIZE	SZ_4K

#define MSM8960_TMR0_PHYS	0x0208A000
#define MSM8960_TMR0_SIZE	SZ_4K

#ifdef CONFIG_DEBUG_MSM8960_UART
#define MSM_DEBUG_UART_BASE	0xF0040000
#define MSM_DEBUG_UART_PHYS	0x16440000
#endif

#endif
