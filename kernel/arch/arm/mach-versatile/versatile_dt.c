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
#include <beep/init.h>
#include <beep/of_irq.h>
#include <beep/of_platform.h>
#include <asm/hardware/vic.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>

#include "core.h"

static void __init versatile_dt_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table,
			     versatile_auxdata_lookup, NULL);
}

static const char *versatile_dt_match[] __initconst = {
	"arm,versatile-ab",
	"arm,versatile-pb",
	NULL,
};

DT_MACHINE_START(VERSATILE_PB, "ARM-Versatile (Device Tree Support)")
	.map_io		= versatile_map_io,
	.init_early	= versatile_init_early,
	.init_irq	= versatile_init_irq,
	.handle_irq	= vic_handle_irq,
	.timer		= &versatile_timer,
	.init_machine	= versatile_dt_init,
	.dt_compat	= versatile_dt_match,
	.restart	= versatile_restart,
MACHINE_END
