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

static int irqmap_ebsa285[] __initdata = { IRQ_IN3, IRQ_IN1, IRQ_IN0, IRQ_PCI };

static int __init ebsa285_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	if (dev->vendor == PCI_VENDOR_ID_CONTAQ &&
	    dev->device == PCI_DEVICE_ID_CONTAQ_82C693)
		switch (PCI_FUNC(dev->devfn)) {
		case 1:	return 14;
		case 2:	return 15;
		case 3:	return 12;
		}

	return irqmap_ebsa285[(slot + pin) & 3];
}

static struct hw_pci ebsa285_pci __initdata = {
	.map_irq		= ebsa285_map_irq,
	.nr_controllers		= 1,
	.ops			= &dc21285_ops,
	.setup			= dc21285_setup,
	.preinit		= dc21285_preinit,
	.postinit		= dc21285_postinit,
};

static int __init ebsa285_init_pci(void)
{
	if (machine_is_ebsa285())
		pci_common_init(&ebsa285_pci);
	return 0;
}

subsys_initcall(ebsa285_init_pci);
