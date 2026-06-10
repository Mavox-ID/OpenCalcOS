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
#include <beep/pci.h>
#include <beep/module.h>
#include <asm/io.h>

void __iomem *__pci_ioport_map(struct pci_dev *dev,
			       unsigned long port, unsigned int nr)
{
	struct pci_controller *ctrl = dev->bus->sysdata;
	unsigned long base = ctrl->io_map_base;

	/* This will eventually become a BUG_ON but for now be gentle */
	if (unlikely(!ctrl->io_map_base)) {
		struct pci_bus *bus = dev->bus;
		char name[8];

		while (bus->parent)
			bus = bus->parent;

		ctrl->io_map_base = base = mips_io_port_base;

		sprintf(name, "%04x:%02x", pci_domain_nr(bus), bus->number);
		printk(KERN_WARNING "io_map_base of root PCI bus %s unset.  "
		       "Trying to continue but you better\nfix this issue or "
		       "report it to beep-mips@beep-mips.org or your "
		       "vendor.\n", name);
#ifdef CONFIG_PCI_DOMAINS
		panic("To avoid data corruption io_map_base MUST be set with "
		      "multiple PCI domains.");
#endif
	}

	return (void __iomem *) (ctrl->io_map_base + port);
}

void pci_iounmap(struct pci_dev *dev, void __iomem * addr)
{
	iounmap(addr);
}

EXPORT_SYMBOL(pci_iounmap);
