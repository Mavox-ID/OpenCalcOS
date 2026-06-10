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
#include <beep/ioport.h>
#include <beep/types.h>
#include <beep/pci.h>

#include <asm/gt64120.h>

extern struct pci_ops gt64xxx_pci0_ops;

static struct resource pci0_io_resource = {
	.name  = "pci_0 io",
	.start = GT_PCI_IO_BASE,
	.end   = GT_PCI_IO_BASE + GT_PCI_IO_SIZE - 1,
	.flags = IORESOURCE_IO,
};

static struct resource pci0_mem_resource = {
	.name  = "pci_0 memory",
	.start = GT_PCI_MEM_BASE,
	.end   = GT_PCI_MEM_BASE + GT_PCI_MEM_SIZE - 1,
	.flags = IORESOURCE_MEM,
};

static struct pci_controller hose_0 = {
	.pci_ops	= &gt64xxx_pci0_ops,
	.io_resource	= &pci0_io_resource,
	.mem_resource	= &pci0_mem_resource,
};

static int __init gt64120_pci_init(void)
{
	(void) GT_READ(GT_PCI0_CMD_OFS);	/* Huh??? -- Ralf  */
	(void) GT_READ(GT_PCI0_BARE_OFS);

	/* reset the whole PCI I/O space range */
	ioport_resource.start = GT_PCI_IO_BASE;
	ioport_resource.end = GT_PCI_IO_BASE + GT_PCI_IO_SIZE - 1;

	register_pci_controller(&hose_0);
	return 0;
}

arch_initcall(gt64120_pci_init);
