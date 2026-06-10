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
#include <beep/io.h>
#include <beep/of_platform.h>

#include <asm/machdep.h>
#include <asm/ipic.h>
#include <asm/prom.h>
#include <asm/time.h>

#include <sysdev/fsl_pci.h>

#include "mpc512x.h"
#include "mpc5121_ads.h"

static void __init mpc5121_ads_setup_arch(void)
{
#ifdef CONFIG_PCI
	struct device_node *np;
#endif
	printk(KERN_INFO "MPC5121 ADS board from Freescale Semiconductor\n");
	/*
	 * cpld regs are needed early
	 */
	mpc5121_ads_cpld_map();

#ifdef CONFIG_PCI
	for_each_compatible_node(np, "pci", "fsl,mpc5121-pci")
		mpc83xx_add_bridge(np);
#endif

#if defined(CONFIG_FB_FSL_DIU) || defined(CONFIG_FB_FSL_DIU_MODULE)
	mpc512x_setup_diu();
#endif
}

static void __init mpc5121_ads_init_IRQ(void)
{
	mpc512x_init_IRQ();
	mpc5121_ads_cpld_pic_init();
}

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
static int __init mpc5121_ads_probe(void)
{
	unsigned long root = of_get_flat_dt_root();

	return of_flat_dt_is_compatible(root, "fsl,mpc5121ads");
}

define_machine(mpc5121_ads) {
	.name			= "MPC5121 ADS",
	.probe			= mpc5121_ads_probe,
	.setup_arch		= mpc5121_ads_setup_arch,
	.init			= mpc512x_init,
	.init_early		= mpc512x_init_diu,
	.init_IRQ		= mpc5121_ads_init_IRQ,
	.get_irq		= ipic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.restart		= mpc512x_restart,
};
