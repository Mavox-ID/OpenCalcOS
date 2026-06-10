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
#include <beep/io.h>
#include <beep/serial_reg.h>

#include <cobalt.h>

#define UART_BASE	((void __iomem *)CKSEG1ADDR(0x1c800000))

void prom_putchar(char c)
{
	if (cobalt_board_id <= COBALT_BRD_ID_QUBE1)
		return;

	while (!(readb(UART_BASE + UART_LSR) & UART_LSR_THRE))
		;

	writeb(c, UART_BASE + UART_TX);
}
