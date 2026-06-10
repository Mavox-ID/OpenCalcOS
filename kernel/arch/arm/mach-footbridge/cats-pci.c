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

/* cats host-specific stuff */
static int irqmap_cats[] __initdata = { IRQ_PCI, IRQ_IN0, IRQ_IN1, IRQ_IN3 };

static u8 cats_no_swizzle(struct pci_dev *dev, u8 *pin)
{
	return 0;
}

static int __init cats_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	if (dev->irq >= 255)
		return -1;	/* not a valid interrupt. */

	if (dev->irq >= 128)
		return dev->irq & 0x1f;

	if (dev->irq >= 1 && dev->irq <= 4)
		return irqmap_cats[dev->irq - 1];

	if (dev->irq != 0)
		printk("PCI: device %02x:%02x has unknown irq line %x\n",
		       dev->bus->number, dev->devfn, dev->irq);

	return -1;
}

/*
 * why not the standard PCI swizzle?  does this prevent 4-port tulip
 * cards being used (ie, pci-pci bridge based cards)?
 */
static struct hw_pci cats_pci __initdata = {
	.swizzle		= cats_no_swizzle,
	.map_irq		= cats_map_irq,
	.nr_controllers		= 1,
	.ops			= &dc21285_ops,
	.setup			= dc21285_setup,
	.preinit		= dc21285_preinit,
	.postinit		= dc21285_postinit,
};

static int __init cats_pci_init(void)
{
	if (machine_is_cats())
		pci_common_init(&cats_pci);
	return 0;
}

subsys_initcall(cats_pci_init);
