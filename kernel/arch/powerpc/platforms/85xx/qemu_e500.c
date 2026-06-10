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
#include <beep/of_fdt.h>
#include <asm/machdep.h>
#include <asm/time.h>
#include <asm/udbg.h>
#include <asm/mpic.h>
#include <sysdev/fsl_soc.h>
#include <sysdev/fsl_pci.h>
#include "smp.h"
#include "mpc85xx.h"

void __init qemu_e500_pic_init(void)
{
	struct mpic *mpic;

	mpic = mpic_alloc(NULL, 0, MPIC_BIG_ENDIAN | MPIC_SINGLE_DEST_CPU,
			0, 256, " OpenPIC  ");

	BUG_ON(mpic == NULL);
	mpic_init(mpic);
}

static void __init qemu_e500_setup_arch(void)
{
	ppc_md.progress("qemu_e500_setup_arch()", 0);

	fsl_pci_assign_primary();
	swiotlb_detect_4g();
	mpc85xx_smp_init();
}

/*
 * Called very early, device-tree isn't unflattened
 */
static int __init qemu_e500_probe(void)
{
	unsigned long root = of_get_flat_dt_root();

	return !!of_flat_dt_is_compatible(root, "fsl,qemu-e500");
}

machine_arch_initcall(qemu_e500, mpc85xx_common_publish_devices);

define_machine(qemu_e500) {
	.name			= "QEMU e500",
	.probe			= qemu_e500_probe,
	.setup_arch		= qemu_e500_setup_arch,
	.init_IRQ		= qemu_e500_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
#endif
	.get_irq		= mpic_get_irq,
	.restart		= fsl_rstcr_restart,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
};
