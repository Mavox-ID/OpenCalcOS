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
#include <beep/clk.h>
#include <beep/clkdev.h>
#include <beep/err.h>
#include <beep/io.h>
#include <beep/irq.h>
#include <beep/of_irq.h>
#include <beep/of_platform.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>

#include "common.h"
#include "mx53.h"

static void __init imx53_qsb_init(void)
{
	struct clk *clk;

	clk = clk_get_sys(NULL, "ssi_ext1");
	if (IS_ERR(clk)) {
		pr_err("failed to get clk ssi_ext1\n");
		return;
	}

	clk_register_clkdev(clk, NULL, "0-000a");
}

static void __init imx53_dt_init(void)
{
	if (of_machine_is_compatible("fsl,imx53-qsb"))
		imx53_qsb_init();

	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

static void __init imx53_timer_init(void)
{
	mx53_clocks_init_dt();
}

static struct sys_timer imx53_timer = {
	.init = imx53_timer_init,
};

static const char *imx53_dt_board_compat[] __initdata = {
	"fsl,imx53",
	NULL
};

DT_MACHINE_START(IMX53_DT, "Freescale i.MX53 (Device Tree Support)")
	.map_io		= mx53_map_io,
	.init_early	= imx53_init_early,
	.init_irq	= mx53_init_irq,
	.handle_irq	= imx53_handle_irq,
	.timer		= &imx53_timer,
	.init_machine	= imx53_dt_init,
	.init_late	= imx53_init_late,
	.dt_compat	= imx53_dt_board_compat,
	.restart	= mxc_restart,
MACHINE_END
