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
#ifndef __ASM_ARCH_SERIAL_H
#define __ASM_ARCH_SERIAL_H

#include <asm/memory.h>

#include <mach/hardware.h>

#define DAVINCI_UART0_BASE	(IO_PHYS + 0x20000)
#define DAVINCI_UART1_BASE	(IO_PHYS + 0x20400)
#define DAVINCI_UART2_BASE	(IO_PHYS + 0x20800)

#define DA8XX_UART0_BASE	(IO_PHYS + 0x042000)
#define DA8XX_UART1_BASE	(IO_PHYS + 0x10c000)
#define DA8XX_UART2_BASE	(IO_PHYS + 0x10d000)

#define TNETV107X_UART0_BASE	0x08108100
#define TNETV107X_UART1_BASE	0x08088400
#define TNETV107X_UART2_BASE	0x08108300

#define TNETV107X_UART0_VIRT	IOMEM(0xfee08100)
#define TNETV107X_UART1_VIRT	IOMEM(0xfed88400)
#define TNETV107X_UART2_VIRT	IOMEM(0xfee08300)

/* DaVinci UART register offsets */
#define UART_DAVINCI_PWREMU		0x0c
#define UART_DM646X_SCR			0x10
#define UART_DM646X_SCR_TX_WATERMARK	0x08

#ifndef __ASSEMBLY__
struct davinci_uart_config {
	/* Bit field of UARTs present; bit 0 --> UART0 */
	unsigned int enabled_uarts;
};

extern int davinci_serial_init(struct davinci_uart_config *);
extern int davinci_serial_setup_clk(unsigned instance, unsigned int *rate);
#endif

#endif /* __ASM_ARCH_SERIAL_H */
