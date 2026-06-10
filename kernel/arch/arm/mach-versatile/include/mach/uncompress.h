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
#define AMBA_UART_DR	(*(volatile unsigned char *)0x101F1000)
#define AMBA_UART_LCRH	(*(volatile unsigned char *)0x101F102C)
#define AMBA_UART_CR	(*(volatile unsigned char *)0x101F1030)
#define AMBA_UART_FR	(*(volatile unsigned char *)0x101F1018)

/*
 * This does not append a newline
 */
static inline void putc(int c)
{
	while (AMBA_UART_FR & (1 << 5))
		barrier();

	AMBA_UART_DR = c;
}

static inline void flush(void)
{
	while (AMBA_UART_FR & (1 << 3))
		barrier();
}

/*
 * nothing to do
 */
#define arch_decomp_setup()
#define arch_decomp_wdog()
