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
#include <beep/of.h>
#include <beep/of_platform.h>
#include <asm/system_misc.h>
#include <asm/mach/arch.h>
#include <mach/orion5x.h>
#include <plat/irq.h>
#include "common.h"

struct of_dev_auxdata orion5x_auxdata_lookup[] __initdata = {
	OF_DEV_AUXDATA("marvell,orion-spi", 0xf1010600, "orion_spi.0", NULL),
	OF_DEV_AUXDATA("marvell,mv64xxx-i2c", 0xf1011000, "mv64xxx_i2c.0",
		       NULL),
	OF_DEV_AUXDATA("marvell,orion-wdt", 0xf1020300, "orion_wdt", NULL),
	OF_DEV_AUXDATA("marvell,orion-sata", 0xf1080000, "sata_mv.0", NULL),
	OF_DEV_AUXDATA("marvell,orion-crypto", 0xf1090000, "mv_crypto", NULL),
	{},
};

static void __init orion5x_dt_init(void)
{
	char *dev_name;
	u32 dev, rev;

	orion5x_id(&dev, &rev, &dev_name);
	printk(KERN_INFO "Orion ID: %s. TCLK=%d.\n", dev_name, orion5x_tclk);

	/*
	 * Setup Orion address map
	 */
	orion5x_setup_cpu_mbus_bridge();

	/* Setup root of clk tree */
	clk_init();

	/*
	 * Don't issue "Wait for Interrupt" instruction if we are
	 * running on D0 5281 silicon.
	 */
	if (dev == MV88F5281_DEV_ID && rev == MV88F5281_REV_D0) {
		printk(KERN_INFO "Orion: Applying 5281 D0 WFI workaround.\n");
		disable_hlt();
	}

	if (of_machine_is_compatible("lacie,ethernet-disk-mini-v2"))
		edmini_v2_init();

	of_platform_populate(NULL, of_default_bus_match_table,
			     orion5x_auxdata_lookup, NULL);
}

static const char *orion5x_dt_compat[] = {
	"marvell,orion5x",
	NULL,
};

DT_MACHINE_START(ORION5X_DT, "Marvell Orion5x (Flattened Device Tree)")
	/* Maintainer: Thomas Petazzoni <thomas.petazzoni@free-electrons.com> */
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion_dt_init_irq,
	.timer		= &orion5x_timer,
	.init_machine	= orion5x_dt_init,
	.restart	= orion5x_restart,
	.dt_compat	= orion5x_dt_compat,
MACHINE_END
