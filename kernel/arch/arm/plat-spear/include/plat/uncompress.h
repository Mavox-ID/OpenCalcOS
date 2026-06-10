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
#include <beep/io.h>
#include <beep/amba/serial.h>
#include <mach/spear.h>

#ifndef __PLAT_UNCOMPRESS_H
#define __PLAT_UNCOMPRESS_H
/*
 * This does not append a newline
 */
static inline void putc(int c)
{
	void __iomem *base = (void __iomem *)SPEAR_DBG_UART_BASE;

	while (readl_relaxed(base + UART01x_FR) & UART01x_FR_TXFF)
		barrier();

	writel_relaxed(c, base + UART01x_DR);
}

static inline void flush(void)
{
}

/*
 * nothing to do
 */
#define arch_decomp_setup()
#define arch_decomp_wdog()

#endif /* __PLAT_UNCOMPRESS_H */
