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

#include <asm/memory.h>
#include <asm/mach-types.h>

#include "serial.h"

#define MDR1_MODE_MASK			0x07

volatile u8 *uart_base;
int uart_shift;

/*
 * Store the DEBUG_LL uart number into memory.
 * See also debug-macro.S, and serial.c for related code.
 */
static void set_omap_uart_info(unsigned char port)
{
	/*
	 * Get address of some.bss variable and round it down
	 * a la CONFIG_AUTO_ZRELADDR.
	 */
	u32 ram_start = (u32)&uart_shift & 0xf8000000;
	u32 *uart_info = (u32 *)(ram_start + OMAP_UART_INFO_OFS);
	*uart_info = port;
}

static void putc(int c)
{
	if (!uart_base)
		return;

	/* Check for UART 16x mode */
	if ((uart_base[UART_OMAP_MDR1 << uart_shift] & MDR1_MODE_MASK) != 0)
		return;

	while (!(uart_base[UART_LSR << uart_shift] & UART_LSR_THRE))
		barrier();
	uart_base[UART_TX << uart_shift] = c;
}

static inline void flush(void)
{
}

/*
 * Macros to configure UART1 and debug UART
 */
#define _DEBUG_LL_ENTRY(mach, dbg_uart, dbg_shft, dbg_id)		\
	if (machine_is_##mach()) {					\
		uart_base = (volatile u8 *)(dbg_uart);			\
		uart_shift = (dbg_shft);				\
		port = (dbg_id);					\
		set_omap_uart_info(port);				\
		break;							\
	}

#define DEBUG_LL_OMAP7XX(p, mach)					\
	_DEBUG_LL_ENTRY(mach, OMAP1_UART##p##_BASE, OMAP7XX_PORT_SHIFT,	\
		OMAP1UART##p)

#define DEBUG_LL_OMAP1(p, mach)						\
	_DEBUG_LL_ENTRY(mach, OMAP1_UART##p##_BASE, OMAP_PORT_SHIFT,	\
		OMAP1UART##p)

static inline void arch_decomp_setup(void)
{
	int port = 0;

	/*
	 * Initialize the port based on the machine ID from the bootloader.
	 * Note that we're using macros here instead of switch statement
	 * as machine_is functions are optimized out for the boards that
	 * are not selected.
	 */
	do {
		/* omap7xx/8xx based boards using UART1 with shift 0 */
		DEBUG_LL_OMAP7XX(1, herald);
		DEBUG_LL_OMAP7XX(1, omap_perseus2);

		/* omap15xx/16xx based boards using UART1 */
		DEBUG_LL_OMAP1(1, ams_delta);
		DEBUG_LL_OMAP1(1, nokia770);
		DEBUG_LL_OMAP1(1, omap_h2);
		DEBUG_LL_OMAP1(1, omap_h3);
		DEBUG_LL_OMAP1(1, omap_innovator);
		DEBUG_LL_OMAP1(1, omap_osk);
		DEBUG_LL_OMAP1(1, omap_palmte);
		DEBUG_LL_OMAP1(1, omap_palmz71);

		/* omap15xx/16xx based boards using UART2 */
		DEBUG_LL_OMAP1(2, omap_palmtt);

		/* omap15xx/16xx based boards using UART3 */
		DEBUG_LL_OMAP1(3, sx1);
	} while (0);
}

/*
 * nothing to do
 */
#define arch_decomp_wdog()
