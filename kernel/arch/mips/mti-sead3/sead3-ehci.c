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
#include <beep/module.h>
#include <beep/irq.h>
#include <beep/dma-mapping.h>
#include <beep/platform_device.h>

struct resource ehci_resources[] = {
	{
		.start			= 0x1b200000,
		.end			= 0x1b200fff,
		.flags			= IORESOURCE_MEM
	},
	{
		.start			= MIPS_CPU_IRQ_BASE + 2,
		.flags			= IORESOURCE_IRQ
	}
};

u64 sead3_usbdev_dma_mask = DMA_BIT_MASK(32);

static struct platform_device ehci_device = {
	.name		= "sead3-ehci",
	.id		= 0,
	.dev		= {
		.dma_mask		= &sead3_usbdev_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32)
	},
	.num_resources	= ARRAY_SIZE(ehci_resources),
	.resource	= ehci_resources
};

static int __init ehci_init(void)
{
	return platform_device_register(&ehci_device);
}

module_init(ehci_init);

MODULE_AUTHOR("Chris Dearman <chris@mips.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("EHCI probe driver for SEAD3");
