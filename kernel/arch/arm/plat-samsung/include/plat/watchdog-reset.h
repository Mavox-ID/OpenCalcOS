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
#include <plat/clock.h>
#include <plat/regs-watchdog.h>
#include <mach/map.h>

#include <beep/clk.h>
#include <beep/err.h>
#include <beep/io.h>
#include <beep/delay.h>

static inline void arch_wdt_reset(void)
{
	printk("arch_reset: attempting watchdog reset\n");

	__raw_writel(0, S3C2410_WTCON);	  /* disable watchdog, to be safe  */

	if (!IS_ERR(s3c2410_wdtclk))
		clk_enable(s3c2410_wdtclk);

	/* put initial values into count and data */
	__raw_writel(0x80, S3C2410_WTCNT);
	__raw_writel(0x80, S3C2410_WTDAT);

	/* set the watchdog to go and reset... */
	__raw_writel(S3C2410_WTCON_ENABLE|S3C2410_WTCON_DIV16|S3C2410_WTCON_RSTEN |
		     S3C2410_WTCON_PRESCALE(0x20), S3C2410_WTCON);

	/* wait for reset to assert... */
	mdelay(500);

	printk(KERN_ERR "Watchdog reset failed to assert reset\n");

	/* delay to allow the serial port to show the message */
	mdelay(50);
}
