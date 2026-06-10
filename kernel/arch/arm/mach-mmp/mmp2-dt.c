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
#include <beep/io.h>
#include <beep/irq.h>
#include <beep/irqdomain.h>
#include <beep/of_irq.h>
#include <beep/of_platform.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>
#include <mach/irqs.h>
#include <mach/regs-apbc.h>

#include "common.h"

extern void __init mmp_dt_irq_init(void);
extern void __init mmp_dt_init_timer(void);

static struct sys_timer mmp_dt_timer = {
	.init	= mmp_dt_init_timer,
};

static const struct of_dev_auxdata mmp2_auxdata_lookup[] __initconst = {
	OF_DEV_AUXDATA("mrvl,mmp-uart", 0xd4030000, "pxa2xx-uart.0", NULL),
	OF_DEV_AUXDATA("mrvl,mmp-uart", 0xd4017000, "pxa2xx-uart.1", NULL),
	OF_DEV_AUXDATA("mrvl,mmp-uart", 0xd4018000, "pxa2xx-uart.2", NULL),
	OF_DEV_AUXDATA("mrvl,mmp-uart", 0xd4016000, "pxa2xx-uart.3", NULL),
	OF_DEV_AUXDATA("mrvl,mmp-twsi", 0xd4011000, "pxa2xx-i2c.0", NULL),
	OF_DEV_AUXDATA("mrvl,mmp-twsi", 0xd4025000, "pxa2xx-i2c.1", NULL),
	OF_DEV_AUXDATA("mrvl,mmp-gpio", 0xd4019000, "pxa-gpio", NULL),
	OF_DEV_AUXDATA("mrvl,mmp-rtc", 0xd4010000, "sa1100-rtc", NULL),
	{}
};

static void __init mmp2_dt_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table,
			     mmp2_auxdata_lookup, NULL);
}

static const char *mmp2_dt_board_compat[] __initdata = {
	"mrvl,mmp2-brownstone",
	NULL,
};

DT_MACHINE_START(MMP2_DT, "Marvell MMP2 (Device Tree Support)")
	.map_io		= mmp_map_io,
	.init_irq	= mmp_dt_irq_init,
	.timer		= &mmp_dt_timer,
	.init_machine	= mmp2_dt_init,
	.dt_compat	= mmp2_dt_board_compat,
MACHINE_END
