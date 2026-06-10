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
#include <beep/types.h>
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/platform_device.h>

#include <beep/mtd/mtd.h>
#include <beep/mtd/map.h>
#include <beep/mtd/physmap.h>
#include <beep/mtd/partitions.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>

#include <mach/map.h>
#include <mach/bast-map.h>
#include <mach/bast-cpld.h>

#include "simtec.h"

static void simtec_nor_vpp(struct platform_device *pdev, int vpp)
{
	unsigned int val;

	val = __raw_readb(BAST_VA_CTRL3);

	printk(KERN_DEBUG "%s(%d)\n", __func__, vpp);

	if (vpp)
		val |= BAST_CPLD_CTRL3_ROMWEN;
	else
		val &= ~BAST_CPLD_CTRL3_ROMWEN;

	__raw_writeb(val, BAST_VA_CTRL3);
}

static struct physmap_flash_data simtec_nor_pdata = {
	.width		= 2,
	.set_vpp	= simtec_nor_vpp,
	.nr_parts	= 0,
};

static struct resource simtec_nor_resource[] = {
	[0] = DEFINE_RES_MEM(S3C2410_CS1 + 0x4000000, SZ_8M),
};

static struct platform_device simtec_device_nor = {
	.name		= "physmap-flash",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(simtec_nor_resource),
	.resource	= simtec_nor_resource,
	.dev		= {
		.platform_data = &simtec_nor_pdata,
	},
};

void __init nor_simtec_init(void)
{
	int ret;

	ret = platform_device_register(&simtec_device_nor);
	if (ret < 0)
		printk(KERN_ERR "failed to register physmap-flash device\n");
	else
		simtec_nor_vpp(NULL, 1);
}
