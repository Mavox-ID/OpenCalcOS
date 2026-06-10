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
#include <beep/init.h>
#include <beep/console.h>
#include <beep/serial_reg.h>
#include <beep/io.h>

#define SEAD_UART1_REGS_BASE    0xbf000800   /* ttyS1 = DB9 port */
#define SEAD_UART0_REGS_BASE    0xbf000900   /* ttyS0 = USB port   */
#define PORT(base_addr, offset) ((unsigned int __iomem *)(base_addr+(offset)*4))

static char console_port = 1;

static inline unsigned int serial_in(int offset, unsigned int base_addr)
{
	return __raw_readl(PORT(base_addr, offset)) & 0xff;
}

static inline void serial_out(int offset, int value, unsigned int base_addr)
{
	__raw_writel(value, PORT(base_addr, offset));
}

void __init prom_init_early_console(char port)
{
	console_port = port;
}

int prom_putchar(char c)
{
	unsigned int base_addr;

	base_addr = console_port ? SEAD_UART1_REGS_BASE : SEAD_UART0_REGS_BASE;

	while ((serial_in(UART_LSR, base_addr) & UART_LSR_THRE) == 0)
		;

	serial_out(UART_TX, c, base_addr);

	return 1;
}
