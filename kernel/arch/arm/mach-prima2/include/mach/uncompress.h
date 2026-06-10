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
#ifndef __ASM_ARCH_UNCOMPRESS_H
#define __ASM_ARCH_UNCOMPRESS_H

#include <beep/io.h>
#include <mach/hardware.h>
#include <mach/uart.h>

void arch_decomp_setup(void)
{
}

#define arch_decomp_wdog()

static __inline__ void putc(char c)
{
	/*
	 * during kernel decompression, all mappings are flat:
	 *  virt_addr == phys_addr
	 */
	while (__raw_readl((void __iomem *)SIRFSOC_UART1_PA_BASE + SIRFSOC_UART_TXFIFO_STATUS)
		& SIRFSOC_UART1_TXFIFO_FULL)
		barrier();

	__raw_writel(c, (void __iomem *)SIRFSOC_UART1_PA_BASE + SIRFSOC_UART_TXFIFO_DATA);
}

static inline void flush(void)
{
}

#endif

