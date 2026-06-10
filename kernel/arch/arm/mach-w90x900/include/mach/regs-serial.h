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
#ifndef __ASM_ARM_REGS_SERIAL_H
#define __ASM_ARM_REGS_SERIAL_H

#define UART0_BA	W90X900_VA_UART
#define UART1_BA	(W90X900_VA_UART+0x100)
#define UART2_BA	(W90X900_VA_UART+0x200)
#define UART3_BA	(W90X900_VA_UART+0x300)
#define UART4_BA	(W90X900_VA_UART+0x400)

#define UART0_PA	W90X900_PA_UART
#define UART1_PA	(W90X900_PA_UART+0x100)
#define UART2_PA	(W90X900_PA_UART+0x200)
#define UART3_PA	(W90X900_PA_UART+0x300)
#define UART4_PA	(W90X900_PA_UART+0x400)

#ifndef __ASSEMBLY__

struct w90x900_uart_clksrc {
	const char	*name;
	unsigned int	divisor;
	unsigned int	min_baud;
	unsigned int	max_baud;
};

struct w90x900_uartcfg {
	unsigned char	hwport;
	unsigned char	unused;
	unsigned short	flags;
	unsigned long	uart_flags;

	unsigned long	ucon;
	unsigned long	ulcon;
	unsigned long	ufcon;

	struct w90x900_uart_clksrc *clocks;
	unsigned int	clocks_size;
};

#endif /* __ASSEMBLY__ */

#endif /* __ASM_ARM_REGS_SERIAL_H */

