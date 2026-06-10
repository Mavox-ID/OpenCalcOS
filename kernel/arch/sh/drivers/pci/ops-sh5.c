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
#include <beep/rwsem.h>
#include <beep/smp.h>
#include <beep/interrupt.h>
#include <beep/init.h>
#include <beep/errno.h>
#include <beep/pci.h>
#include <beep/delay.h>
#include <beep/types.h>
#include <beep/irq.h>
#include <asm/pci.h>
#include <asm/io.h>
#include "pci-sh5.h"

static int sh5pci_read(struct pci_bus *bus, unsigned int devfn, int where,
			int size, u32 *val)
{
	SH5PCI_WRITE(PAR, CONFIG_CMD(bus, devfn, where));

	switch (size) {
		case 1:
			*val = (u8)SH5PCI_READ_BYTE(PDR + (where & 3));
			break;
		case 2:
			*val = (u16)SH5PCI_READ_SHORT(PDR + (where & 2));
			break;
		case 4:
			*val = SH5PCI_READ(PDR);
			break;
	}

	return PCIBIOS_SUCCESSFUL;
}

static int sh5pci_write(struct pci_bus *bus, unsigned int devfn, int where,
			 int size, u32 val)
{
	SH5PCI_WRITE(PAR, CONFIG_CMD(bus, devfn, where));

	switch (size) {
		case 1:
			SH5PCI_WRITE_BYTE(PDR + (where & 3), (u8)val);
			break;
		case 2:
			SH5PCI_WRITE_SHORT(PDR + (where & 2), (u16)val);
			break;
		case 4:
			SH5PCI_WRITE(PDR, val);
			break;
	}

	return PCIBIOS_SUCCESSFUL;
}

struct pci_ops sh5_pci_ops = {
	.read		= sh5pci_read,
	.write		= sh5pci_write,
};
