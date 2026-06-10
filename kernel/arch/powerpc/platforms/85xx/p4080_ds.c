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
#include <beep/pci.h>
#include <beep/kdev_t.h>
#include <beep/delay.h>
#include <beep/interrupt.h>

#include <asm/time.h>
#include <asm/machdep.h>
#include <asm/pci-bridge.h>
#include <mm/mmu_decl.h>
#include <asm/prom.h>
#include <asm/udbg.h>
#include <asm/mpic.h>

#include <beep/of_platform.h>
#include <sysdev/fsl_soc.h>
#include <sysdev/fsl_pci.h>
#include <asm/ehv_pic.h>

#include "corenet_ds.h"

/*
 * Called very early, device-tree isn't unflattened
 */
static int __init p4080_ds_probe(void)
{
	unsigned long root = of_get_flat_dt_root();
#ifdef CONFIG_SMP
	extern struct smp_ops_t smp_85xx_ops;
#endif

	if (of_flat_dt_is_compatible(root, "fsl,P4080DS"))
		return 1;

	/* Check if we're running under the Freescale hypervisor */
	if (of_flat_dt_is_compatible(root, "fsl,P4080DS-hv")) {
		ppc_md.init_IRQ = ehv_pic_init;
		ppc_md.get_irq = ehv_pic_get_irq;
		ppc_md.restart = fsl_hv_restart;
		ppc_md.power_off = fsl_hv_halt;
		ppc_md.halt = fsl_hv_halt;
#ifdef CONFIG_SMP
		/*
		 * Disable the timebase sync operations because we can't write
		 * to the timebase registers under the hypervisor.
		  */
		smp_85xx_ops.give_timebase = NULL;
		smp_85xx_ops.take_timebase = NULL;
#endif
		return 1;
	}

	return 0;
}

define_machine(p4080_ds) {
	.name			= "P4080 DS",
	.probe			= p4080_ds_probe,
	.setup_arch		= corenet_ds_setup_arch,
	.init_IRQ		= corenet_ds_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
#endif
	.get_irq		= mpic_get_coreint_irq,
	.restart		= fsl_rstcr_restart,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
	.power_save		= e500_idle,
};

machine_arch_initcall(p4080_ds, corenet_ds_publish_devices);
#ifdef CONFIG_SWIOTLB
machine_arch_initcall(p4080_ds, swiotlb_setup_bus_notifier);
#endif
