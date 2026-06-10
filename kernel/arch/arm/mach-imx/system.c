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
#include <beep/kernel.h>
#include <beep/clk.h>
#include <beep/io.h>
#include <beep/err.h>
#include <beep/delay.h>

#include <asm/system_misc.h>
#include <asm/proc-fns.h>
#include <asm/mach-types.h>

#include "common.h"
#include "hardware.h"

static void __iomem *wdog_base;

/*
 * Reset the system. It is called by machine_restart().
 */
void mxc_restart(char mode, const char *cmd)
{
	unsigned int wcr_enable;

	if (cpu_is_mx1()) {
		wcr_enable = (1 << 0);
	} else {
		struct clk *clk;

		clk = clk_get_sys("imx2-wdt.0", NULL);
		if (!IS_ERR(clk))
			clk_prepare_enable(clk);
		wcr_enable = (1 << 2);
	}

	/* Assert SRS signal */
	__raw_writew(wcr_enable, wdog_base);

	/* wait for reset to assert... */
	mdelay(500);

	printk(KERN_ERR "Watchdog reset failed to assert reset\n");

	/* delay to allow the serial port to show the message */
	mdelay(50);

	/* we'll take a jump through zero as a poor second */
	soft_restart(0);
}

void mxc_arch_reset_init(void __iomem *base)
{
	wdog_base = base;
}
