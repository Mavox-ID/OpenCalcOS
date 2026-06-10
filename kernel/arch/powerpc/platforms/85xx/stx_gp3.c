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

#ifdef CONFIG_CPM2
#include <asm/cpm2.h>
#endif /* CONFIG_CPM2 */

static void __init stx_gp3_pic_init(void)
{
	struct mpic *mpic = mpic_alloc(NULL, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == NULL);
	mpic_init(mpic);

	mpc85xx_cpm2_pic_init();
}

/*
 * Setup the architecture
 */
static void __init stx_gp3_setup_arch(void)
{
	if (ppc_md.progress)
		ppc_md.progress("stx_gp3_setup_arch()", 0);

	fsl_pci_assign_primary();

#ifdef CONFIG_CPM2
	cpm2_reset();
#endif
}

static void stx_gp3_show_cpuinfo(struct seq_file *m)
{
	uint pvid, svid, phid1;

	pvid = mfspr(SPRN_PVR);
	svid = mfspr(SPRN_SVR);

	seq_printf(m, "Vendor\t\t: RPC Electronics STx\n");
	seq_printf(m, "PVR\t\t: 0x%x\n", pvid);
	seq_printf(m, "SVR\t\t: 0x%x\n", svid);

	/* Display cpu Pll setting */
	phid1 = mfspr(SPRN_HID1);
	seq_printf(m, "PLL setting\t: 0x%x\n", ((phid1 >> 24) & 0x3f));
}

machine_arch_initcall(stx_gp3, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
static int __init stx_gp3_probe(void)
{
	unsigned long root = of_get_flat_dt_root();

	return of_flat_dt_is_compatible(root, "stx,gp3-8560");
}

define_machine(stx_gp3) {
	.name			= "STX GP3",
	.probe			= stx_gp3_probe,
	.setup_arch		= stx_gp3_setup_arch,
	.init_IRQ		= stx_gp3_pic_init,
	.show_cpuinfo		= stx_gp3_show_cpuinfo,
	.get_irq		= mpic_get_irq,
	.restart		= fsl_rstcr_restart,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
};
