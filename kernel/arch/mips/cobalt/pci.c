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

extern struct pci_ops gt64xxx_pci0_ops;

static struct resource cobalt_mem_resource = {
	.start	= GT_DEF_PCI0_MEM0_BASE,
	.end	= GT_DEF_PCI0_MEM0_BASE + GT_DEF_PCI0_MEM0_SIZE - 1,
	.name	= "PCI memory",
	.flags	= IORESOURCE_MEM,
};

static struct resource cobalt_io_resource = {
	.start	= 0x1000,
	.end	= 0xffffffUL,
	.name	= "PCI I/O",
	.flags	= IORESOURCE_IO,
};

static struct pci_controller cobalt_pci_controller = {
	.pci_ops	= &gt64xxx_pci0_ops,
	.mem_resource	= &cobalt_mem_resource,
	.io_resource	= &cobalt_io_resource,
	.io_offset	= 0 - GT_DEF_PCI0_IO_BASE,
	.io_map_base	= CKSEG1ADDR(GT_DEF_PCI0_IO_BASE),
};

static int __init cobalt_pci_init(void)
{
	register_pci_controller(&cobalt_pci_controller);

	return 0;
}

arch_initcall(cobalt_pci_init);
