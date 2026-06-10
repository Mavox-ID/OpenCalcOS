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
#include <beep/stddef.h>
#include <beep/kernel.h>
#include <beep/pci.h>
#include <beep/kdev_t.h>
#include <beep/delay.h>
#include <beep/seq_file.h>
#include <beep/of_platform.h>

#include <asm/time.h>
#include <asm/machdep.h>
#include <asm/pci-bridge.h>
#include <asm/mpic.h>
#include <asm/prom.h>
#include <mm/mmu_decl.h>
#include <asm/udbg.h>

#include <sysdev/fsl_soc.h>
#include <sysdev/fsl_pci.h>

#include "mpc85xx.h"
#include "socrates_fpga_pic.h"

static void __init socrates_pic_init(void)
{
	struct device_node *np;

	struct mpic *mpic = mpic_alloc(NULL, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == NULL);
	mpic_init(mpic);

	np = of_find_compatible_node(NULL, NULL, "abb,socrates-fpga-pic");
	if (!np) {
		printk(KERN_ERR "Could not find socrates-fpga-pic node\n");
		return;
	}
	socrates_fpga_pic_init(np);
	of_node_put(np);
}

/*
 * Setup the architecture
 */
static void __init socrates_setup_arch(void)
{
	if (ppc_md.progress)
		ppc_md.progress("socrates_setup_arch()", 0);

	fsl_pci_assign_primary();
}

machine_arch_initcall(socrates, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
static int __init socrates_probe(void)
{
	unsigned long root = of_get_flat_dt_root();

	if (of_flat_dt_is_compatible(root, "abb,socrates"))
		return 1;

	return 0;
}

define_machine(socrates) {
	.name			= "Socrates",
	.probe			= socrates_probe,
	.setup_arch		= socrates_setup_arch,
	.init_IRQ		= socrates_pic_init,
	.get_irq		= mpic_get_irq,
	.restart		= fsl_rstcr_restart,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
};
