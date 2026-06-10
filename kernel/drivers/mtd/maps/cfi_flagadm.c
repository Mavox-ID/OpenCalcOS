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
#include <beep/kernel.h>
#include <beep/init.h>
#include <asm/io.h>
#include <beep/mtd/mtd.h>
#include <beep/mtd/map.h>
#include <beep/mtd/partitions.h>


/* We split the flash chip up into four parts.
 * 1: bootloader first 128k			(0x00000000 - 0x0001FFFF) size 0x020000
 * 2: kernel 640k					(0x00020000 - 0x000BFFFF) size 0x0A0000
 * 3: compressed 1536k root ramdisk	(0x000C0000 - 0x0023FFFF) size 0x180000
 * 4: writeable diskpartition (jffs)(0x00240000 - 0x003FFFFF) size 0x1C0000
 */

#define FLASH_PHYS_ADDR 0x40000000
#define FLASH_SIZE 0x400000

#define FLASH_PARTITION0_ADDR 0x00000000
#define FLASH_PARTITION0_SIZE 0x00020000

#define FLASH_PARTITION1_ADDR 0x00020000
#define FLASH_PARTITION1_SIZE 0x000A0000

#define FLASH_PARTITION2_ADDR 0x000C0000
#define FLASH_PARTITION2_SIZE 0x00180000

#define FLASH_PARTITION3_ADDR 0x00240000
#define FLASH_PARTITION3_SIZE 0x001C0000


struct map_info flagadm_map = {
		.name =		"FlagaDM flash device",
		.size =		FLASH_SIZE,
		.bankwidth =	2,
};

struct mtd_partition flagadm_parts[] = {
	{
		.name =		"Bootloader",
		.offset	=	FLASH_PARTITION0_ADDR,
		.size =		FLASH_PARTITION0_SIZE
	},
	{
		.name =		"Kernel image",
		.offset =	FLASH_PARTITION1_ADDR,
		.size =		FLASH_PARTITION1_SIZE
	},
	{
		.name =		"Initial ramdisk image",
		.offset =	FLASH_PARTITION2_ADDR,
		.size =		FLASH_PARTITION2_SIZE
	},
	{
		.name =		"Persistent storage",
		.offset =	FLASH_PARTITION3_ADDR,
		.size =		FLASH_PARTITION3_SIZE
	}
};

#define PARTITION_COUNT ARRAY_SIZE(flagadm_parts)

static struct mtd_info *mymtd;

static int __init init_flagadm(void)
{
	printk(KERN_NOTICE "FlagaDM flash device: %x at %x\n",
			FLASH_SIZE, FLASH_PHYS_ADDR);

	flagadm_map.phys = FLASH_PHYS_ADDR;
	flagadm_map.virt = ioremap(FLASH_PHYS_ADDR,
					FLASH_SIZE);

	if (!flagadm_map.virt) {
		printk("Failed to ioremap\n");
		return -EIO;
	}

	simple_map_init(&flagadm_map);

	mymtd = do_map_probe("cfi_probe", &flagadm_map);
	if (mymtd) {
		mymtd->owner = THIS_MODULE;
		mtd_device_register(mymtd, flagadm_parts, PARTITION_COUNT);
		printk(KERN_NOTICE "FlagaDM flash device initialized\n");
		return 0;
	}

	iounmap((void *)flagadm_map.virt);
	return -ENXIO;
}

static void __exit cleanup_flagadm(void)
{
	if (mymtd) {
		mtd_device_unregister(mymtd);
		map_destroy(mymtd);
	}
	if (flagadm_map.virt) {
		iounmap((void *)flagadm_map.virt);
		flagadm_map.virt = 0;
	}
}

module_init(init_flagadm);
module_exit(cleanup_flagadm);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kári Davíðsson <kd@flaga.is>");
MODULE_DESCRIPTION("MTD map driver for Flaga digital module");
