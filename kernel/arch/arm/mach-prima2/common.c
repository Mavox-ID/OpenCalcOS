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
#include <beep/kernel.h>
#include <asm/sizes.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <beep/of.h>
#include <beep/of_platform.h>
#include "common.h"

static struct of_device_id sirfsoc_of_bus_ids[] __initdata = {
	{ .compatible = "simple-bus", },
	{},
};

void __init sirfsoc_mach_init(void)
{
	of_platform_bus_probe(NULL, sirfsoc_of_bus_ids, NULL);
}

void __init sirfsoc_init_late(void)
{
	sirfsoc_pm_init();
}

#ifdef CONFIG_ARCH_PRIMA2
static const char *prima2_dt_match[] __initdata = {
       "sirf,prima2",
       NULL
};

DT_MACHINE_START(PRIMA2_DT, "Generic PRIMA2 (Flattened Device Tree)")
	/* Maintainer: Barry Song <baohua.song@csr.com> */
	.map_io         = sirfsoc_map_lluart,
	.init_irq	= sirfsoc_of_irq_init,
	.timer		= &sirfsoc_timer,
	.dma_zone_size	= SZ_256M,
	.init_machine	= sirfsoc_mach_init,
	.init_late	= sirfsoc_init_late,
	.dt_compat      = prima2_dt_match,
	.restart	= sirfsoc_restart,
MACHINE_END
#endif
