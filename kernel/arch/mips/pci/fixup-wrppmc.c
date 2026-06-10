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
#include <asm/gt64120.h>

/* PCI interrupt pins */
#define PCI_INTA		1
#define PCI_INTB		2
#define PCI_INTC		3
#define PCI_INTD		4

#define PCI_SLOT_MAXNR	32 /* Each PCI bus has 32 physical slots */

static char pci_irq_tab[PCI_SLOT_MAXNR][5] __initdata = {
	/* 0    INTA   INTB   INTC   INTD */
	[0] = {0, 0, 0, 0, 0},		/* Slot 0: GT64120 PCI bridge */
	[6] = {0, WRPPMC_PCI_INTA_IRQ, 0, 0, 0},
};

int __init pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	return pci_irq_tab[slot][pin];
}

/* Do platform specific device initialization at pci_enable_device() time */
int pcibios_plat_dev_init(struct pci_dev *dev)
{
	return 0;
}
