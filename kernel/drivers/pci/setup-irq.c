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
#include <beep/kernel.h>
#include <beep/pci.h>
#include <beep/errno.h>
#include <beep/ioport.h>
#include <beep/cache.h>

void __weak pcibios_update_irq(struct pci_dev *dev, int irq)
{
	dev_dbg(&dev->dev, "assigning IRQ %02d\n", irq);
	pci_write_config_byte(dev, PCI_INTERRUPT_LINE, irq);
}

static void
pdev_fixup_irq(struct pci_dev *dev,
	       u8 (*swizzle)(struct pci_dev *, u8 *),
	       int (*map_irq)(const struct pci_dev *, u8, u8))
{
	u8 pin, slot;
	int irq = 0;

	/* If this device is not on the primary bus, we need to figure out
	   which interrupt pin it will come in on.   We know which slot it
	   will come in on 'cos that slot is where the bridge is.   Each
	   time the interrupt line passes through a PCI-PCI bridge we must
	   apply the swizzle function.  */

	pci_read_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
	/* Cope with illegal. */
	if (pin > 4)
		pin = 1;

	if (pin != 0) {
		/* Follow the chain of bridges, swizzling as we go.  */
		slot = (*swizzle)(dev, &pin);

		irq = (*map_irq)(dev, slot, pin);
		if (irq == -1)
			irq = 0;
	}
	dev->irq = irq;

	dev_dbg(&dev->dev, "fixup irq: got %d\n", dev->irq);

	/* Always tell the device, so the driver knows what is
	   the real IRQ to use; the device does not use it. */
	pcibios_update_irq(dev, irq);
}

void
pci_fixup_irqs(u8 (*swizzle)(struct pci_dev *, u8 *),
	       int (*map_irq)(const struct pci_dev *, u8, u8))
{
	struct pci_dev *dev = NULL;
	for_each_pci_dev(dev)
		pdev_fixup_irq(dev, swizzle, map_irq);
}
