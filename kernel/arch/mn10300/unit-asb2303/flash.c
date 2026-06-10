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
#include <beep/mtd/partitions.h>
#include <beep/mtd/physmap.h>

#define ASB2303_PROM_ADDR	0xA0000000	/* Boot PROM */
#define ASB2303_PROM_SIZE	(2 * 1024 * 1024)
#define ASB2303_FLASH_ADDR	0xA4000000	/* System Flash */
#define ASB2303_FLASH_SIZE	(32 * 1024 * 1024)
#define ASB2303_CONFIG_ADDR	0xA6000000	/* System Config EEPROM */
#define ASB2303_CONFIG_SIZE	(8 * 1024)

/*
 * default MTD partition table for both main flash devices, expected to be
 * overridden by RedBoot
 */
static struct mtd_partition asb2303_partitions[] = {
	{
		.name		= "Bootloader",
		.size		= 0x00040000,
		.offset		= 0,
		.mask_flags	= MTD_CAP_ROM /* force read-only */
	}, {
		.name		= "Kernel",
		.size		= 0x00400000,
		.offset		= 0x00040000,
	}, {
		.name		= "Filesystem",
		.size		= MTDPART_SIZ_FULL,
		.offset		= 0x00440000
	}
};

/*
 * the ASB2303 Boot PROM definition
 */
static struct physmap_flash_data asb2303_bootprom_data = {
	.width		= 2,
	.nr_parts	= 1,
	.parts		= asb2303_partitions,
};

static struct resource asb2303_bootprom_resource = {
	.start		= ASB2303_PROM_ADDR,
	.end		= ASB2303_PROM_ADDR + ASB2303_PROM_SIZE,
	.flags		= IORESOURCE_MEM,
};

static struct platform_device asb2303_bootprom = {
	.name		= "physmap-flash",
	.id		= 0,
	.dev.platform_data = &asb2303_bootprom_data,
	.num_resources	= 1,
	.resource	= &asb2303_bootprom_resource,
};

/*
 * the ASB2303 System Flash definition
 */
static struct physmap_flash_data asb2303_sysflash_data = {
	.width		= 4,
	.nr_parts	= 1,
	.parts		= asb2303_partitions,
};

static struct resource asb2303_sysflash_resource = {
	.start		= ASB2303_FLASH_ADDR,
	.end		= ASB2303_FLASH_ADDR + ASB2303_FLASH_SIZE,
	.flags		= IORESOURCE_MEM,
};

static struct platform_device asb2303_sysflash = {
	.name		= "physmap-flash",
	.id		= 1,
	.dev.platform_data = &asb2303_sysflash_data,
	.num_resources	= 1,
	.resource	= &asb2303_sysflash_resource,
};

/*
 * register the ASB2303 flashes
 */
static int __init asb2303_mtd_init(void)
{
	platform_device_register(&asb2303_bootprom);
	platform_device_register(&asb2303_sysflash);
	return 0;
}

module_init(asb2303_mtd_init);
