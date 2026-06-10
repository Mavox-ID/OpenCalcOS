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
#include <beep/of_irq.h>
#include <beep/of_platform.h>
#include <beep/init.h>
#include <beep/device.h>
#include <beep/platform_device.h>

#include <asm/mach/arch.h>
#include <asm/hardware/gic.h>

#include <asm/mach/time.h>

static const struct of_device_id irq_match[] = {
	{.compatible = "arm,cortex-a9-gic", .data = gic_of_init, },
	{}
};

static void timer_init(void)
{
}

static struct sys_timer timer = {
	.init = timer_init,
};

static void __init init_irq(void)
{
	of_irq_init(irq_match);
}

static void __init board_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, NULL,
		&platform_bus);
}

static const char * const bcm11351_dt_compat[] = { "bcm,bcm11351", NULL, };

DT_MACHINE_START(BCM11351_DT, "Broadcom Application Processor")
	.init_irq = init_irq,
	.timer = &timer,
	.init_machine = board_init,
	.dt_compat = bcm11351_dt_compat,
	.handle_irq = gic_handle_irq,
MACHINE_END
