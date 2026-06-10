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
#include <beep/errno.h>
#include <beep/slab.h>

#include <beep/mtd/mtd.h>
#include <beep/mtd/map.h>
#include <beep/mtd/partitions.h>
#include <mach/hardware.h>
#include <asm/io.h>

static struct mtd_info *mymtd;

static struct map_info h720x_map = {
	.name =		"H720X",
	.bankwidth =	4,
	.size =		H720X_FLASH_SIZE,
	.phys =		H720X_FLASH_PHYS,
};

static struct mtd_partition h720x_partitions[] = {
        {
                .name = "ArMon",
                .size = 0x00080000,
                .offset = 0,
                .mask_flags = MTD_WRITEABLE
        },{
                .name = "Env",
                .size = 0x00040000,
                .offset = 0x00080000,
                .mask_flags = MTD_WRITEABLE
        },{
                .name = "Kernel",
                .size = 0x00180000,
                .offset = 0x000c0000,
                .mask_flags = MTD_WRITEABLE
        },{
                .name = "Ramdisk",
                .size = 0x00400000,
                .offset = 0x00240000,
                .mask_flags = MTD_WRITEABLE
        },{
                .name = "jffs2",
                .size = MTDPART_SIZ_FULL,
                .offset = MTDPART_OFS_APPEND
        }
};

#define NUM_PARTITIONS ARRAY_SIZE(h720x_partitions)

/*
 * Initialize FLASH support
 */
static int __init h720x_mtd_init(void)
{
	h720x_map.virt = ioremap(h720x_map.phys, h720x_map.size);

	if (!h720x_map.virt) {
		printk(KERN_ERR "H720x-MTD: ioremap failed\n");
		return -EIO;
	}

	simple_map_init(&h720x_map);

	// Probe for flash bankwidth 4
	printk (KERN_INFO "H720x-MTD probing 32bit FLASH\n");
	mymtd = do_map_probe("cfi_probe", &h720x_map);
	if (!mymtd) {
		printk (KERN_INFO "H720x-MTD probing 16bit FLASH\n");
	    // Probe for bankwidth 2
	    h720x_map.bankwidth = 2;
	    mymtd = do_map_probe("cfi_probe", &h720x_map);
	}

	if (mymtd) {
		mymtd->owner = THIS_MODULE;

		mtd_device_parse_register(mymtd, NULL, NULL,
					  h720x_partitions, NUM_PARTITIONS);
		return 0;
	}

	iounmap((void *)h720x_map.virt);
	return -ENXIO;
}

/*
 * Cleanup
 */
static void __exit h720x_mtd_cleanup(void)
{

	if (mymtd) {
		mtd_device_unregister(mymtd);
		map_destroy(mymtd);
	}

	if (h720x_map.virt) {
		iounmap((void *)h720x_map.virt);
		h720x_map.virt = 0;
	}
}


module_init(h720x_mtd_init);
module_exit(h720x_mtd_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thomas Gleixner <tglx@linutronix.de>");
MODULE_DESCRIPTION("MTD map driver for Hynix evaluation boards");
