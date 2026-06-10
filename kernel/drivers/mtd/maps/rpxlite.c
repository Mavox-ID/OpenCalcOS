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


#define WINDOW_ADDR 0xfe000000
#define WINDOW_SIZE 0x800000

static struct mtd_info *mymtd;

static struct map_info rpxlite_map = {
	.name = "RPX",
	.size = WINDOW_SIZE,
	.bankwidth = 4,
	.phys = WINDOW_ADDR,
};

static int __init init_rpxlite(void)
{
	printk(KERN_NOTICE "RPX Lite or CLLF flash device: %x at %x\n", WINDOW_SIZE*4, WINDOW_ADDR);
	rpxlite_map.virt = ioremap(WINDOW_ADDR, WINDOW_SIZE * 4);

	if (!rpxlite_map.virt) {
		printk("Failed to ioremap\n");
		return -EIO;
	}
	simple_map_init(&rpxlite_map);
	mymtd = do_map_probe("cfi_probe", &rpxlite_map);
	if (mymtd) {
		mymtd->owner = THIS_MODULE;
		mtd_device_register(mymtd, NULL, 0);
		return 0;
	}

	iounmap((void *)rpxlite_map.virt);
	return -ENXIO;
}

static void __exit cleanup_rpxlite(void)
{
	if (mymtd) {
		mtd_device_unregister(mymtd);
		map_destroy(mymtd);
	}
	if (rpxlite_map.virt) {
		iounmap((void *)rpxlite_map.virt);
		rpxlite_map.virt = 0;
	}
}

module_init(init_rpxlite);
module_exit(cleanup_rpxlite);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arnold Christensen <AKC@pel.dk>");
MODULE_DESCRIPTION("MTD map driver for RPX Lite and CLLF boards");
