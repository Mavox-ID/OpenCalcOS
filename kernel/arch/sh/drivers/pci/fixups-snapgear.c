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
#include <beep/types.h>
#include <beep/init.h>
#include <beep/pci.h>
#include <beep/sh_intc.h>
#include "pci-sh4.h"

int __init pcibios_map_platform_irq(const struct pci_dev *pdev, u8 slot, u8 pin)
{
	int irq = -1;

	switch (slot) {
	case 8:  /* the PCI bridge */ break;
	case 11: irq = evt2irq(0x300); break; /* USB    */
	case 12: irq = evt2irq(0x360); break; /* PCMCIA */
	case 13: irq = evt2irq(0x2a0); break; /* eth0   */
	case 14: irq = evt2irq(0x300); break; /* eth1   */
	case 15: irq = evt2irq(0x360); break; /* safenet (unused) */
	}

	printk("PCI: Mapping SnapGear IRQ for slot %d, pin %c to irq %d\n",
	       slot, pin - 1 + 'A', irq);

	return irq;
}
