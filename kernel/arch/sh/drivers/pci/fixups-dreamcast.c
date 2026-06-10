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
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/interrupt.h>
#include <beep/init.h>
#include <beep/irq.h>
#include <beep/pci.h>
#include <beep/dma-mapping.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <mach/pci.h>

static void gapspci_fixup_resources(struct pci_dev *dev)
{
	struct pci_channel *p = dev->sysdata;

	printk(KERN_NOTICE "PCI: Fixing up device %s\n", pci_name(dev));

	switch (dev->device) {
	case PCI_DEVICE_ID_SEGA_BBA:
		/*
		 * We also assume that dev->devfn == 0
		 */
		dev->resource[1].start	= p->resources[0].start  + 0x100;
		dev->resource[1].end	= dev->resource[1].start + 0x200 - 1;

		/*
		 * This is not a normal BAR, prevent any attempts to move
		 * the BAR, as this will result in a bus lock.
		 */
		dev->resource[1].flags |= IORESOURCE_PCI_FIXED;

		/*
		 * Redirect dma memory allocations to special memory window.
		 */
		BUG_ON(!dma_declare_coherent_memory(&dev->dev,
						GAPSPCI_DMA_BASE,
						GAPSPCI_DMA_BASE,
						GAPSPCI_DMA_SIZE,
						DMA_MEMORY_MAP |
						DMA_MEMORY_EXCLUSIVE));
		break;
	default:
		printk("PCI: Failed resource fixup\n");
	}
}
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, gapspci_fixup_resources);

int __init pcibios_map_platform_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	/*
	 * The interrupt routing semantics here are quite trivial.
	 *
	 * We basically only support one interrupt, so we only bother
	 * updating a device's interrupt line with this single shared
	 * interrupt. Keeps routing quite simple, doesn't it?
	 */
	return GAPSPCI_IRQ;
}
