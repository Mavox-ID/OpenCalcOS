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
#include <beep/platform_device.h>
#include <beep/interrupt.h>
#include <beep/mtd/physmap.h>
#include <beep/io.h>
#include <beep/sh_eth.h>
#include <beep/sh_intc.h>
#include <asm/machvec.h>
#include <asm/sizes.h>

/* NOR Flash */
static struct mtd_partition espt_nor_flash_partitions[] = {
	{
		.name = "U-Boot",
		.offset = 0,
		.size = (2 * SZ_128K),
		.mask_flags = MTD_WRITEABLE,	/* Read-only */
	}, {
		.name = "Beep-Kernel",
		.offset = MTDPART_OFS_APPEND,
		.size = (20 * SZ_128K),
	}, {
		.name = "Root Filesystem",
		.offset = MTDPART_OFS_APPEND,
		.size = MTDPART_SIZ_FULL,
	},
};

static struct physmap_flash_data espt_nor_flash_data = {
	.width = 2,
	.parts = espt_nor_flash_partitions,
	.nr_parts = ARRAY_SIZE(espt_nor_flash_partitions),
};

static struct resource espt_nor_flash_resources[] = {
	[0] = {
		.name = "NOR Flash",
		.start = 0,
		.end = SZ_8M - 1,
		.flags = IORESOURCE_MEM,
	},
};

static struct platform_device espt_nor_flash_device = {
	.name = "physmap-flash",
	.resource = espt_nor_flash_resources,
	.num_resources = ARRAY_SIZE(espt_nor_flash_resources),
	.dev = {
		.platform_data = &espt_nor_flash_data,
	},
};

/* SH-Ether */
static struct resource sh_eth_resources[] = {
	{
		.start  = 0xFEE00800,   /* use eth1 */
		.end    = 0xFEE00F7C - 1,
		.flags  = IORESOURCE_MEM,
	}, {
		.start  = 0xFEE01800,   /* TSU */
		.end    = 0xFEE01FFF,
		.flags  = IORESOURCE_MEM,
	}, {

		.start  = evt2irq(0x920),   /* irq number */
		.flags  = IORESOURCE_IRQ,
	},
};

static struct sh_eth_plat_data sh7763_eth_pdata = {
	.phy = 0,
	.edmac_endian = EDMAC_LITTLE_ENDIAN,
	.register_type = SH_ETH_REG_GIGABIT,
	.phy_interface = PHY_INTERFACE_MODE_MII,
};

static struct platform_device espt_eth_device = {
	.name       = "sh-eth",
	.resource   = sh_eth_resources,
	.num_resources  = ARRAY_SIZE(sh_eth_resources),
	.dev        = {
		.platform_data = &sh7763_eth_pdata,
	},
};

static struct platform_device *espt_devices[] __initdata = {
	&espt_nor_flash_device,
	&espt_eth_device,
};

static int __init espt_devices_setup(void)
{
	return platform_add_devices(espt_devices,
				    ARRAY_SIZE(espt_devices));
}
device_initcall(espt_devices_setup);

static struct sh_machine_vector mv_espt __initmv = {
	.mv_name = "ESPT-GIGA",
};
