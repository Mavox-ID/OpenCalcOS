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
#ifndef __ASM_ARCH_MSM_IOMAP_H
#define __ASM_ARCH_MSM_IOMAP_H

#include <asm/sizes.h>

/* Physical base address and size of peripherals.
 * Ordered by the virtual base addresses they will be mapped at.
 *
 * MSM_VIC_BASE must be an value that can be loaded via a "mov"
 * instruction, otherwise entry-macro.S will not compile.
 *
 * If you add or remove entries here, you'll want to edit the
 * msm_io_desc array in arch/arm/mach-msm/io.c to reflect your
 * changes.
 *
 */

#if defined(CONFIG_ARCH_MSM7X30)
#include "msm_iomap-7x30.h"
#elif defined(CONFIG_ARCH_QSD8X50)
#include "msm_iomap-8x50.h"
#else
#include "msm_iomap-7x00.h"
#endif

#include "msm_iomap-8x60.h"
#include "msm_iomap-8960.h"

#define MSM_DEBUG_UART_SIZE	SZ_4K
#if defined(CONFIG_DEBUG_MSM_UART1)
#define MSM_DEBUG_UART_BASE	0xE1000000
#define MSM_DEBUG_UART_PHYS	MSM_UART1_PHYS
#elif defined(CONFIG_DEBUG_MSM_UART2)
#define MSM_DEBUG_UART_BASE	0xE1000000
#define MSM_DEBUG_UART_PHYS	MSM_UART2_PHYS
#elif defined(CONFIG_DEBUG_MSM_UART3)
#define MSM_DEBUG_UART_BASE	0xE1000000
#define MSM_DEBUG_UART_PHYS	MSM_UART3_PHYS
#endif

/* Virtual addresses shared across all MSM targets. */
#define MSM_CSR_BASE		IOMEM(0xE0001000)
#define MSM_QGIC_DIST_BASE	IOMEM(0xF0000000)
#define MSM_QGIC_CPU_BASE	IOMEM(0xF0001000)
#define MSM_TMR_BASE		IOMEM(0xF0200000)
#define MSM_TMR0_BASE		IOMEM(0xF0201000)
#define MSM_GPIO1_BASE		IOMEM(0xE0003000)
#define MSM_GPIO2_BASE		IOMEM(0xE0004000)

#endif
