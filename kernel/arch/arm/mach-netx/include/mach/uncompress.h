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
/*
 * The following code assumes the serial port has already been
 * initialized by the bootloader.  We search for the first enabled
 * port in the most probable order.  If you didn't setup a port in
 * your bootloader then nothing will appear (which might be desired).
 *
 * This does not append a newline
 */

#define REG(x) (*(volatile unsigned long *)(x))

#define UART1_BASE 0x100a00
#define UART2_BASE 0x100a80

#define UART_DR 0x0

#define UART_CR 0x14
#define CR_UART_EN (1<<0)

#define UART_FR 0x18
#define FR_BUSY (1<<3)
#define FR_TXFF (1<<5)

static void putc(char c)
{
	unsigned long base;

	if (REG(UART1_BASE + UART_CR) & CR_UART_EN)
		base = UART1_BASE;
	else if (REG(UART2_BASE + UART_CR) & CR_UART_EN)
		base = UART2_BASE;
	else
		return;

	while (REG(base + UART_FR) & FR_TXFF);
	REG(base + UART_DR) = c;
}

static inline void flush(void)
{
	unsigned long base;

	if (REG(UART1_BASE + UART_CR) & CR_UART_EN)
		base = UART1_BASE;
	else if (REG(UART2_BASE + UART_CR) & CR_UART_EN)
		base = UART2_BASE;
	else
		return;

	while (REG(base + UART_FR) & FR_BUSY);
}

/*
 * nothing to do
 */
#define arch_decomp_setup()
#define arch_decomp_wdog()
