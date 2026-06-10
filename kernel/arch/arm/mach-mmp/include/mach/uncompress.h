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
#include <mach/addr-map.h>
#include <asm/mach-types.h>

#define UART1_BASE	(APB_PHYS_BASE + 0x36000)
#define UART2_BASE	(APB_PHYS_BASE + 0x17000)
#define UART3_BASE	(APB_PHYS_BASE + 0x18000)

volatile unsigned long *UART;

static inline void putc(char c)
{
	/* UART enabled? */
	if (!(UART[UART_IER] & UART_IER_UUE))
		return;

	while (!(UART[UART_LSR] & UART_LSR_THRE))
		barrier();

	UART[UART_TX] = c;
}

/*
 * This does not append a newline
 */
static inline void flush(void)
{
}

static inline void arch_decomp_setup(void)
{
	/* default to UART2 */
	UART = (unsigned long *)UART2_BASE;

	if (machine_is_avengers_lite())
		UART = (unsigned long *)UART3_BASE;
}

/*
 * nothing to do
 */

#define arch_decomp_wdog()
