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
#include <beep/interrupt.h>

#include <beep/platform_device.h>
#include <beep/ata_platform.h>

#include <asm/mach-types.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>

#include <mach/map.h>
#include <mach/bast-map.h>
#include <mach/bast-irq.h>

/* IDE ports */

static struct pata_platform_info bast_ide_platdata = {
	.ioport_shift	= 5,
};

#define IDE_CS	S3C2410_CS5

static struct resource bast_ide0_resource[] = {
	[0] = DEFINE_RES_MEM(IDE_CS + BAST_PA_IDEPRI, 8 * 0x20),
	[1] = DEFINE_RES_MEM(IDE_CS + BAST_PA_IDEPRIAUX + (6 * 0x20), 0x20),
	[2] = DEFINE_RES_IRQ(IRQ_IDE0),
};

static struct platform_device bast_device_ide0 = {
	.name		= "pata_platform",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(bast_ide0_resource),
	.resource	= bast_ide0_resource,
	.dev		= {
		.platform_data = &bast_ide_platdata,
		.coherent_dma_mask = ~0,
	}

};

static struct resource bast_ide1_resource[] = {
	[0] = DEFINE_RES_MEM(IDE_CS + BAST_PA_IDESEC, 8 * 0x20),
	[1] = DEFINE_RES_MEM(IDE_CS + BAST_PA_IDESECAUX + (6 * 0x20), 0x20),
	[2] = DEFINE_RES_IRQ(IRQ_IDE1),
};

static struct platform_device bast_device_ide1 = {
	.name		= "pata_platform",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(bast_ide1_resource),
	.resource	= bast_ide1_resource,
	.dev		= {
		.platform_data = &bast_ide_platdata,
		.coherent_dma_mask = ~0,
	}
};

static struct platform_device *bast_ide_devices[] __initdata = {
	&bast_device_ide0,
	&bast_device_ide1,
};

static __init int bast_ide_init(void)
{
	if (machine_is_bast() || machine_is_vr1000())
		return platform_add_devices(bast_ide_devices,
					    ARRAY_SIZE(bast_ide_devices));

	return 0;
}

fs_initcall(bast_ide_init);
