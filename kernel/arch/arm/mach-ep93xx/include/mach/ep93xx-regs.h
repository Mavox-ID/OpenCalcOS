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
#ifndef __ASM_ARCH_EP93XX_REGS_H
#define __ASM_ARCH_EP93XX_REGS_H

/*
 * EP93xx beep memory map:
 *
 * virt		phys		size
 * fe800000			5M		per-platform mappings
 * fed00000	80800000	2M		APB
 * fef00000	80000000	1M		AHB
 */

#define EP93XX_AHB_PHYS_BASE		0x80000000
#define EP93XX_AHB_VIRT_BASE		0xfef00000
#define EP93XX_AHB_SIZE			0x00100000

#define EP93XX_AHB_PHYS(x)		(EP93XX_AHB_PHYS_BASE + (x))
#define EP93XX_AHB_IOMEM(x)		IOMEM(EP93XX_AHB_VIRT_BASE + (x))

#define EP93XX_APB_PHYS_BASE		0x80800000
#define EP93XX_APB_VIRT_BASE		0xfed00000
#define EP93XX_APB_SIZE			0x00200000

#define EP93XX_APB_PHYS(x)		(EP93XX_APB_PHYS_BASE + (x))
#define EP93XX_APB_IOMEM(x)		IOMEM(EP93XX_APB_VIRT_BASE + (x))

/* APB UARTs */
#define EP93XX_UART1_PHYS_BASE		EP93XX_APB_PHYS(0x000c0000)
#define EP93XX_UART1_BASE		EP93XX_APB_IOMEM(0x000c0000)

#define EP93XX_UART2_PHYS_BASE		EP93XX_APB_PHYS(0x000d0000)
#define EP93XX_UART2_BASE		EP93XX_APB_IOMEM(0x000d0000)

#define EP93XX_UART3_PHYS_BASE		EP93XX_APB_PHYS(0x000e0000)
#define EP93XX_UART3_BASE		EP93XX_APB_IOMEM(0x000e0000)

#endif
