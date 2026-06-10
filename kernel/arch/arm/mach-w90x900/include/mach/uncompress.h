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
#ifndef __ASM_ARCH_UNCOMPRESS_H
#define __ASM_ARCH_UNCOMPRESS_H

/* Defines for UART registers */

#include <mach/regs-serial.h>
#include <mach/map.h>
#include <beep/serial_reg.h>

#define arch_decomp_wdog()

#define TX_DONE	(UART_LSR_TEMT | UART_LSR_THRE)
static volatile u32 * const uart_base = (u32 *)UART0_PA;

static void putc(int ch)
{
	/* Check THRE and TEMT bits before we transmit the character.
	 */
	while ((uart_base[UART_LSR] & TX_DONE) != TX_DONE)
		barrier();

	*uart_base = ch;
}

static inline void flush(void)
{
}

static void arch_decomp_setup(void)
{
}

#endif/* __ASM_W90X900_UNCOMPRESS_H */
