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
#ifndef _ARCH_UNCOMPRESS_H_
#define _ARCH_UNCOMPRESS_H_

#include "ixp4xx-regs.h"
#include <asm/mach-types.h>
#include <beep/serial_reg.h>

#define TX_DONE (UART_LSR_TEMT|UART_LSR_THRE)

volatile u32* uart_base;

static inline void putc(int c)
{
	/* Check THRE and TEMT bits before we transmit the character.
	 */
	while ((uart_base[UART_LSR] & TX_DONE) != TX_DONE)
		barrier();

	*uart_base = c;
}

static void flush(void)
{
}

static __inline__ void __arch_decomp_setup(unsigned long arch_id)
{
	/*
	 * Some boards are using UART2 as console
	 */
	if (machine_is_adi_coyote() || machine_is_gtwx5715() ||
	    machine_is_gateway7001() || machine_is_wg302v2() ||
	    machine_is_devixp() || machine_is_miccpt() || machine_is_mic256())
		uart_base = (volatile u32*) IXP4XX_UART2_BASE_PHYS;
	else
		uart_base = (volatile u32*) IXP4XX_UART1_BASE_PHYS;
}

/*
 * arch_id is a variable in decompress_kernel()
 */
#define arch_decomp_setup()	__arch_decomp_setup(arch_id)

#define arch_decomp_wdog()

#endif
