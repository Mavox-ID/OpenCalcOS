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
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/interrupt.h>
#include <beep/init.h>
#include <beep/irq.h>
#include <beep/pci.h>
#include <beep/module.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <mach/pci.h>

static struct resource gapspci_resources[] = {
	{
		.name	= "GAPSPCI IO",
		.start	= GAPSPCI_BBA_CONFIG,
		.end	= GAPSPCI_BBA_CONFIG + GAPSPCI_BBA_CONFIG_SIZE - 1,
		.flags	= IORESOURCE_IO,
	},  {
		.name	= "GAPSPCI mem",
		.start	= GAPSPCI_DMA_BASE,
		.end	= GAPSPCI_DMA_BASE + GAPSPCI_DMA_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
};

static struct pci_channel dreamcast_pci_controller = {
	.pci_ops	= &gapspci_pci_ops,
	.resources	= gapspci_resources,
	.nr_resources	= ARRAY_SIZE(gapspci_resources),
	.io_offset	= 0x00000000,
	.mem_offset	= 0x00000000,
};

/*
 * gapspci init
 */

static int __init gapspci_init(void)
{
	char idbuf[16];
	int i;

	/*
	 * FIXME: All of this wants documenting to some degree,
	 * even some basic register definitions would be nice.
	 *
	 * I haven't seen anything this ugly since.. maple.
	 */

	for (i=0; i<16; i++)
		idbuf[i] = inb(GAPSPCI_REGS+i);

	if (strncmp(idbuf, "GAPSPCI_BRIDGE_2", 16))
		return -ENODEV;

	outl(0x5a14a501, GAPSPCI_REGS+0x18);

	for (i=0; i<1000000; i++)
		cpu_relax();

	if (inl(GAPSPCI_REGS+0x18) != 1)
		return -EINVAL;

	outl(0x01000000, GAPSPCI_REGS+0x20);
	outl(0x01000000, GAPSPCI_REGS+0x24);

	outl(GAPSPCI_DMA_BASE, GAPSPCI_REGS+0x28);
	outl(GAPSPCI_DMA_BASE+GAPSPCI_DMA_SIZE, GAPSPCI_REGS+0x2c);

	outl(1, GAPSPCI_REGS+0x14);
	outl(1, GAPSPCI_REGS+0x34);

	/* Setting Broadband Adapter */
	outw(0xf900, GAPSPCI_BBA_CONFIG+0x06);
	outl(0x00000000, GAPSPCI_BBA_CONFIG+0x30);
	outb(0x00, GAPSPCI_BBA_CONFIG+0x3c);
	outb(0xf0, GAPSPCI_BBA_CONFIG+0x0d);
	outw(0x0006, GAPSPCI_BBA_CONFIG+0x04);
	outl(0x00002001, GAPSPCI_BBA_CONFIG+0x10);
	outl(0x01000000, GAPSPCI_BBA_CONFIG+0x14);

	return register_pci_controller(&dreamcast_pci_controller);
}
arch_initcall(gapspci_init);
