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

#include <asm/mach-types.h>

#include <mach/serial.h>

#define IOMEM(x)	((void __force __iomem *)(x))

u32 *uart;

/* PORT_16C550A, in polled non-fifo mode */
static void putc(char c)
{
	if (!uart)
		return;

	while (!(uart[UART_LSR] & UART_LSR_THRE))
		barrier();
	uart[UART_TX] = c;
}

static inline void flush(void)
{
	if (!uart)
		return;

	while (!(uart[UART_LSR] & UART_LSR_THRE))
		barrier();
}

static inline void set_uart_info(u32 phys)
{
	uart = (u32 *)phys;
}

#define _DEBUG_LL_ENTRY(machine, phys)				\
	{							\
		if (machine_is_##machine()) {			\
			set_uart_info(phys);			\
			break;					\
		}						\
	}

#define DEBUG_LL_DAVINCI(machine, port)				\
	_DEBUG_LL_ENTRY(machine, DAVINCI_UART##port##_BASE)

#define DEBUG_LL_DA8XX(machine, port)				\
	_DEBUG_LL_ENTRY(machine, DA8XX_UART##port##_BASE)

#define DEBUG_LL_TNETV107X(machine, port)			\
	_DEBUG_LL_ENTRY(machine, TNETV107X_UART##port##_BASE)

static inline void __arch_decomp_setup(unsigned long arch_id)
{
	/*
	 * Initialize the port based on the machine ID from the bootloader.
	 * Note that we're using macros here instead of switch statement
	 * as machine_is functions are optimized out for the boards that
	 * are not selected.
	 */
	do {
		/* Davinci boards */
		DEBUG_LL_DAVINCI(davinci_evm,		0);
		DEBUG_LL_DAVINCI(sffsdr,		0);
		DEBUG_LL_DAVINCI(neuros_osd2,		0);
		DEBUG_LL_DAVINCI(davinci_dm355_evm,	0);
		DEBUG_LL_DAVINCI(dm355_leopard,		0);
		DEBUG_LL_DAVINCI(davinci_dm6467_evm,	0);
		DEBUG_LL_DAVINCI(davinci_dm365_evm,	0);

		/* DA8xx boards */
		DEBUG_LL_DA8XX(davinci_da830_evm,	2);
		DEBUG_LL_DA8XX(davinci_da850_evm,	2);
		DEBUG_LL_DA8XX(mityomapl138,		1);
		DEBUG_LL_DA8XX(omapl138_hawkboard,	2);

		/* TNETV107x boards */
		DEBUG_LL_TNETV107X(tnetv107x,		1);
	} while (0);
}

#define arch_decomp_setup()	__arch_decomp_setup(arch_id)
#define arch_decomp_wdog()
