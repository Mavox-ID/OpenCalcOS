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
#include <beep/types.h>
#include <beep/serial_reg.h>
#include <beep/init.h>

#include <asm/addrspace.h>

#if defined(CONFIG_MACH_LOONGSON) || defined(CONFIG_MIPS_MALTA)
#define UART_BASE 0x1fd003f8
#define PORT(offset) (CKSEG1ADDR(UART_BASE) + (offset))
#endif

#ifdef CONFIG_AR7
#include <ar7.h>
#define PORT(offset) (CKSEG1ADDR(AR7_REGS_UART0) + (4 * offset))
#endif

#ifdef CONFIG_MACH_JZ4740
#define UART0_BASE  0xB0030000
#define PORT(offset) (UART0_BASE + (4 * offset))
#endif

#ifndef PORT
#error please define the serial port address for your own machine
#endif

static inline unsigned int serial_in(int offset)
{
	return *((char *)PORT(offset));
}

static inline void serial_out(int offset, int value)
{
	*((char *)PORT(offset)) = value;
}

void putc(char c)
{
	int timeout = 1024;

	while (((serial_in(UART_LSR) & UART_LSR_THRE) == 0) && (timeout-- > 0))
		;

	serial_out(UART_TX, c);
}
