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
#ifndef __MACH_PRIMA2_SIRFSOC_UART_H
#define __MACH_PRIMA2_SIRFSOC_UART_H

/* UART-1: used as serial debug port */
#define SIRFSOC_UART1_PA_BASE          0xb0060000
#define SIRFSOC_UART1_VA_BASE          SIRFSOC_VA(0x060000)
#define SIRFSOC_UART1_SIZE		SZ_4K

#define SIRFSOC_UART_TXFIFO_STATUS	0x0114
#define SIRFSOC_UART_TXFIFO_DATA	0x0118

#define SIRFSOC_UART1_TXFIFO_FULL                       (1 << 5)
#define SIRFSOC_UART1_TXFIFO_EMPTY			(1 << 6)

#endif
