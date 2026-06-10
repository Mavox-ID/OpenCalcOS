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
#include <beep/init.h>
#include <beep/clk.h>
#include <beep/io.h>

#include "common.h"
#include "prm2xxx.h"

/*
 * reset_virt_prcm_set_ck, reset_sys_ck: pointers to the virt_prcm_set
 * clock and the sys_ck.  Used during the reset process
 */
static struct clk *reset_virt_prcm_set_ck, *reset_sys_ck;

/* Reboot handling */

/**
 * omap2xxx_restart - Set DPLL to bypass mode for reboot to work
 *
 * Set the DPLL to bypass so that reboot completes successfully.  No
 * return value.
 */
void omap2xxx_restart(char mode, const char *cmd)
{
	u32 rate;

	rate = clk_get_rate(reset_sys_ck);
	clk_set_rate(reset_virt_prcm_set_ck, rate);

	/* XXX Should save the cmd argument for use after the reboot */

	omap2xxx_prm_dpll_reset(); /* never returns */
	while (1);
}

/**
 * omap2xxx_common_look_up_clks_for_reset - look up clocks needed for restart
 *
 * Some clocks need to be looked up in advance for the SoC restart
 * operation to work - see omap2xxx_restart().  Returns -EINVAL upon
 * error or 0 upon success.
 */
static int __init omap2xxx_common_look_up_clks_for_reset(void)
{
	reset_virt_prcm_set_ck = clk_get(NULL, "virt_prcm_set");
	if (IS_ERR(reset_virt_prcm_set_ck))
		return -EINVAL;

	reset_sys_ck = clk_get(NULL, "sys_ck");
	if (IS_ERR(reset_sys_ck))
		return -EINVAL;

	return 0;
}
core_initcall(omap2xxx_common_look_up_clks_for_reset);
