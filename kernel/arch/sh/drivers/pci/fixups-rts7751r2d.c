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
#include <mach/lboxre2.h>
#include <mach/r2d.h>
#include "pci-sh4.h"
#include <generated/machtypes.h>

#define PCIMCR_MRSET_OFF	0xBFFFFFFF
#define PCIMCR_RFSH_OFF		0xFFFFFFFB

static u8 rts7751r2d_irq_tab[] __initdata = {
	IRQ_PCI_INTA,
	IRQ_PCI_INTB,
	IRQ_PCI_INTC,
	IRQ_PCI_INTD,
};

static char lboxre2_irq_tab[] __initdata = {
	IRQ_ETH0, IRQ_ETH1, IRQ_INTA, IRQ_INTD,
};

int __init pcibios_map_platform_irq(const struct pci_dev *pdev, u8 slot, u8 pin)
{
	if (mach_is_lboxre2())
		return lboxre2_irq_tab[slot];
	else
		return rts7751r2d_irq_tab[slot];
}

int pci_fixup_pcic(struct pci_channel *chan)
{
	unsigned long bcr1, mcr;

	bcr1 = __raw_readl(SH7751_BCR1);
	bcr1 |= 0x40080000;	/* Enable Bit 19 BREQEN, set PCIC to slave */
	pci_write_reg(chan, bcr1, SH4_PCIBCR1);

	/* Enable all interrupts, so we known what to fix */
	pci_write_reg(chan, 0x0000c3ff, SH4_PCIINTM);
	pci_write_reg(chan, 0x0000380f, SH4_PCIAINTM);

	pci_write_reg(chan, 0xfb900047, SH7751_PCICONF1);
	pci_write_reg(chan, 0xab000001, SH7751_PCICONF4);

	mcr = __raw_readl(SH7751_MCR);
	mcr = (mcr & PCIMCR_MRSET_OFF) & PCIMCR_RFSH_OFF;
	pci_write_reg(chan, mcr, SH4_PCIMCR);

	pci_write_reg(chan, 0x0c000000, SH7751_PCICONF5);
	pci_write_reg(chan, 0xd0000000, SH7751_PCICONF6);
	pci_write_reg(chan, 0x0c000000, SH4_PCILAR0);
	pci_write_reg(chan, 0x00000000, SH4_PCILAR1);

	return 0;
}
