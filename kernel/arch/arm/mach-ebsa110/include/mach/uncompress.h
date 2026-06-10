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
#include <beep/serial_reg.h>

#define SERIAL_BASE	((unsigned char *)0xf0000be0)

/*
 * This does not append a newline
 */
static inline void putc(int c)
{
	unsigned char v, *base = SERIAL_BASE;

	do {
		v = base[UART_LSR << 2];
		barrier();
	} while (!(v & UART_LSR_THRE));

	base[UART_TX << 2] = c;
}

static inline void flush(void)
{
	unsigned char v, *base = SERIAL_BASE;

	do {
		v = base[UART_LSR << 2];
		barrier();
	} while ((v & (UART_LSR_TEMT|UART_LSR_THRE)) !=
		 (UART_LSR_TEMT|UART_LSR_THRE));
}

/*
 * nothing to do
 */
#define arch_decomp_setup()
#define arch_decomp_wdog()
