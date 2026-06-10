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
#include <asm/types.h>
#include <asm/mach-types.h>
#include <beep/serial_reg.h>
#include <mach/hardware.h>

volatile u32 *uart_base;

#define TX_DONE		(UART_LSR_TEMT | UART_LSR_THRE)

static inline void putc(char c)
{
	while ((uart_base[UART_LSR] & TX_DONE) != TX_DONE)
		barrier();
	uart_base[UART_TX] = c;
}

static inline void flush(void)
{
}

static __inline__ void __arch_decomp_setup(unsigned long arch_id)
{
	if (machine_is_iq80331() || machine_is_iq80332())
		uart_base = (volatile u32 *)IOP33X_UART0_PHYS;
	else
		uart_base = (volatile u32 *)0xfe800000;
}

/*
 * nothing to do
 */
#define arch_decomp_setup()	__arch_decomp_setup(arch_id)
#define arch_decomp_wdog()
