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
#undef DEBUG

#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/clk.h>
#include <beep/io.h>

#include "soc.h"
#include "clock.h"
#include "clock2xxx.h"
#include "cm.h"
#include "cm-regbits-24xx.h"

struct clk_hw *dclk_hw;
/*
 * Omap24xx specific clock functions
 */

/*
 * Switch the MPU rate if specified on cmdline.  We cannot do this
 * early until cmdline is parsed.  XXX This should be removed from the
 * clock code and handled by the OPP layer code in the near future.
 */
static int __init omap2xxx_clk_arch_init(void)
{
	int ret;

	if (!cpu_is_omap24xx())
		return 0;

	ret = omap2_clk_switch_mpurate_at_boot("virt_prcm_set");
	if (!ret)
		omap2_clk_print_new_rates("sys_ck", "dpll_ck", "mpu_ck");

	return ret;
}

arch_initcall(omap2xxx_clk_arch_init);


