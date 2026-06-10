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
#include <beep/init.h>

#include <asm/irq.h>
#include <asm/mach/pci.h>
#include <asm/mach-types.h>

/*
 * We now use the slot ID instead of the device identifiers to select
 * which interrupt is routed where.
 */
static int __init netwinder_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	switch (slot) {
	case 0:  /* host bridge */
		return 0;

	case 9:  /* CyberPro */
		return IRQ_NETWINDER_VGA;

	case 10: /* DC21143 */
		return IRQ_NETWINDER_ETHER100;

	case 12: /* Winbond 553 */
		return IRQ_ISA_HARDDISK1;

	case 13: /* Winbond 89C940F */
		return IRQ_NETWINDER_ETHER10;

	default:
		printk(KERN_ERR "PCI: unknown device in slot %s\n",
			pci_name(dev));
		return 0;
	}
}

static struct hw_pci netwinder_pci __initdata = {
	.map_irq		= netwinder_map_irq,
	.nr_controllers		= 1,
	.ops			= &dc21285_ops,
	.setup			= dc21285_setup,
	.preinit		= dc21285_preinit,
	.postinit		= dc21285_postinit,
};

static int __init netwinder_pci_init(void)
{
	if (machine_is_netwinder())
		pci_common_init(&netwinder_pci);
	return 0;
}

subsys_initcall(netwinder_pci_init);
