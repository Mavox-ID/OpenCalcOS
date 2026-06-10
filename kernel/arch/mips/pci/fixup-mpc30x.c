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
#include <beep/init.h>
#include <beep/pci.h>

#include <asm/vr41xx/mpc30x.h>

static const int internal_func_irqs[] __initconst = {
	VRC4173_CASCADE_IRQ,
	VRC4173_AC97_IRQ,
	VRC4173_USB_IRQ,
};

static const int irq_tab_mpc30x[] __initconst = {
 [12] = VRC4173_PCMCIA1_IRQ,
 [13] = VRC4173_PCMCIA2_IRQ,
 [29] = MQ200_IRQ,
};

int __init pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	if (slot == 30)
		return internal_func_irqs[PCI_FUNC(dev->devfn)];

	return irq_tab_mpc30x[slot];
}

/* Do platform specific device initialization at pci_enable_device() time */
int pcibios_plat_dev_init(struct pci_dev *dev)
{
	return 0;
}
