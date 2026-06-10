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
#include <beep/types.h>
#include <asm/txx9/pci.h>
#include <asm/txx9/jmr3927.h>

int __init jmr3927_pci_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	unsigned char irq = pin;

	/* IRQ rotation (PICMG) */
	irq--;			/* 0-3 */
	if (slot == TX3927_PCIC_IDSEL_AD_TO_SLOT(23)) {
		/* PCI CardSlot (IDSEL=A23, DevNu=12) */
		/* PCIA => PCIC (IDSEL=A23) */
		/* NOTE: JMR3927 JP1 must be set to OPEN */
		irq = (irq + 2) % 4;
	} else if (slot == TX3927_PCIC_IDSEL_AD_TO_SLOT(22)) {
		/* PCI CardSlot (IDSEL=A22, DevNu=11) */
		/* PCIA => PCIA (IDSEL=A22) */
		/* NOTE: JMR3927 JP1 must be set to OPEN */
		irq = (irq + 0) % 4;
	} else {
		/* PCI Backplane */
		if (txx9_pci_option & TXX9_PCI_OPT_PICMG)
			irq = (irq + 33 - slot) % 4;
		else
			irq = (irq + 3 + slot) % 4;
	}
	irq++;			/* 1-4 */

	switch (irq) {
	case 1:
		irq = JMR3927_IRQ_IOC_PCIA;
		break;
	case 2:
		irq = JMR3927_IRQ_IOC_PCIB;
		break;
	case 3:
		irq = JMR3927_IRQ_IOC_PCIC;
		break;
	case 4:
		irq = JMR3927_IRQ_IOC_PCID;
		break;
	}

	/* Check OnBoard Ethernet (IDSEL=A24, DevNu=13) */
	if (dev->bus->parent == NULL &&
	    slot == TX3927_PCIC_IDSEL_AD_TO_SLOT(24))
		irq = JMR3927_IRQ_ETHER0;
	return irq;
}
