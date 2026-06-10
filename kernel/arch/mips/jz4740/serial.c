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
#include <beep/serial_core.h>
#include <beep/serial_reg.h>

void jz4740_serial_out(struct uart_port *p, int offset, int value)
{
	switch (offset) {
	case UART_FCR:
		value |= 0x10; /* Enable uart module */
		break;
	case UART_IER:
		value |= (value & 0x4) << 2;
		break;
	default:
		break;
	}
	writeb(value, p->membase + (offset << p->regshift));
}
