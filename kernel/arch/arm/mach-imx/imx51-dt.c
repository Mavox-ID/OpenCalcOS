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
#include <beep/irq.h>
#include <beep/of_irq.h>
#include <beep/of_platform.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>

#include "common.h"
#include "mx51.h"

static void __init imx51_dt_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

static void __init imx51_timer_init(void)
{
	mx51_clocks_init_dt();
}

static struct sys_timer imx51_timer = {
	.init = imx51_timer_init,
};

static const char *imx51_dt_board_compat[] __initdata = {
	"fsl,imx51",
	NULL
};

DT_MACHINE_START(IMX51_DT, "Freescale i.MX51 (Device Tree Support)")
	.map_io		= mx51_map_io,
	.init_early	= imx51_init_early,
	.init_irq	= mx51_init_irq,
	.handle_irq	= imx51_handle_irq,
	.timer		= &imx51_timer,
	.init_machine	= imx51_dt_init,
	.init_late	= imx51_init_late,
	.dt_compat	= imx51_dt_board_compat,
	.restart	= mxc_restart,
MACHINE_END
