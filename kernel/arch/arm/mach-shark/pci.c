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
#include <beep/pci.h>
#include <beep/init.h>
#include <beep/io.h>
#include <video/vga.h>

#include <asm/irq.h>
#include <asm/mach/pci.h>
#include <asm/mach-types.h>

#define IO_START	0x40000000

static int __init shark_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	if (dev->bus->number == 0)
		if (dev->devfn == 0)
			return 255;
		else
			return 11;
	else
		return 255;
}

extern void __init via82c505_preinit(void);

static struct hw_pci shark_pci __initdata = {
	.setup		= via82c505_setup,
	.map_irq	= shark_map_irq,
	.nr_controllers = 1,
	.ops		= &via82c505_ops,
	.preinit	= via82c505_preinit,
};

static int __init shark_pci_init(void)
{
	if (!machine_is_shark())
		return -ENODEV;

	pcibios_min_io = 0x6000;
	pcibios_min_mem = 0x50000000;
	vga_base = 0xe8000000;

	pci_ioremap_io(0, IO_START);

	pci_common_init(&shark_pci);

	return 0;
}

subsys_initcall(shark_pci_init);
