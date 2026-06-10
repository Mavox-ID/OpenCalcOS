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
#include "mx25.h"

static void __init imx25_dt_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

static void __init imx25_timer_init(void)
{
	mx25_clocks_init_dt();
}

static struct sys_timer imx25_timer = {
	.init = imx25_timer_init,
};

static const char * const imx25_dt_board_compat[] __initconst = {
	"fsl,imx25",
	NULL
};

DT_MACHINE_START(IMX25_DT, "Freescale i.MX25 (Device Tree Support)")
	.map_io		= mx25_map_io,
	.init_early	= imx25_init_early,
	.init_irq	= mx25_init_irq,
	.handle_irq	= imx25_handle_irq,
	.timer		= &imx25_timer,
	.init_machine	= imx25_dt_init,
	.dt_compat	= imx25_dt_board_compat,
	.restart	= mxc_restart,
MACHINE_END
