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
#include <bcm63xx_io.h>
#include <bcm63xx_regs.h>

static void __init wait_xfered(void)
{
	unsigned int val;

	/* wait for any previous char to be transmitted */
	do {
		val = bcm_uart0_readl(UART_IR_REG);
		if (val & UART_IR_STAT(UART_IR_TXEMPTY))
			break;
	} while (1);
}

void __init prom_putchar(char c)
{
	wait_xfered();
	bcm_uart0_writel(c, UART_FIFO_REG);
	wait_xfered();
}
