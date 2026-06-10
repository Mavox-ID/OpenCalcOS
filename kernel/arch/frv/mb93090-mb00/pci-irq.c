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
#include <beep/kernel.h>
#include <beep/pci.h>
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/irq.h>

#include <asm/io.h>
#include <asm/smp.h>

#include "pci-frv.h"

/*
 *	DEVICE	DEVNO	INT#A	INT#B	INT#C	INT#D
 *	=======	=======	=======	=======	=======	=======
 *	MB86943	0	fpga.10	-	-	-
 *	RTL8029	16	fpga.12	-	-	-
 *	SLOT 1	19	fpga.6	fpga.5	fpga.4	fpga.3
 *	SLOT 2	18	fpga.5	fpga.4	fpga.3	fpga.6
 *	SLOT 3	17	fpga.4	fpga.3	fpga.6	fpga.5
 *
 */

static const uint8_t __initconst pci_bus0_irq_routing[32][4] = {
	[0 ] = { IRQ_FPGA_MB86943_PCI_INTA },
	[16] = { IRQ_FPGA_RTL8029_INTA },
	[17] = { IRQ_FPGA_PCI_INTC, IRQ_FPGA_PCI_INTD, IRQ_FPGA_PCI_INTA, IRQ_FPGA_PCI_INTB },
	[18] = { IRQ_FPGA_PCI_INTB, IRQ_FPGA_PCI_INTC, IRQ_FPGA_PCI_INTD, IRQ_FPGA_PCI_INTA },
	[19] = { IRQ_FPGA_PCI_INTA, IRQ_FPGA_PCI_INTB, IRQ_FPGA_PCI_INTC, IRQ_FPGA_PCI_INTD },
};

void __init pcibios_irq_init(void)
{
}

void __init pcibios_fixup_irqs(void)
{
	struct pci_dev *dev = NULL;
	uint8_t line, pin;

	for_each_pci_dev(dev) {
		pci_read_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
		if (pin) {
			dev->irq = pci_bus0_irq_routing[PCI_SLOT(dev->devfn)][pin - 1];
			pci_write_config_byte(dev, PCI_INTERRUPT_LINE, dev->irq);
		}
		pci_read_config_byte(dev, PCI_INTERRUPT_LINE, &line);
	}
}

void __init pcibios_penalize_isa_irq(int irq)
{
}

void pcibios_enable_irq(struct pci_dev *dev)
{
	pci_write_config_byte(dev, PCI_INTERRUPT_LINE, dev->irq);
}
