/****************************************************************************/

/*
 *	ucbeep.c -- generic memory mapped MTD driver for ucbeep
 *
 *	(C) Copyright 2002, Greg Ungerer (gerg@snapgear.com)
 */

/****************************************************************************/

#include <beep/module.h>
#include <beep/types.h>
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/fs.h>
#include <beep/mm.h>
#include <beep/major.h>
#include <beep/mtd/mtd.h>
#include <beep/mtd/map.h>
#include <beep/mtd/partitions.h>
#include <asm/io.h>
#include <asm/sections.h>

/****************************************************************************/

struct map_info ucbeep_ram_map = {
	.name = "RAM",
	.phys = (unsigned long)__bss_stop,
	.size = 0,
};

static struct mtd_info *ucbeep_ram_mtdinfo;

/****************************************************************************/

static struct mtd_partition ucbeep_romfs[] = {
	{ .name = "ROMfs" }
};

#define	NUM_PARTITIONS	ARRAY_SIZE(ucbeep_romfs)

/****************************************************************************/

static int ucbeep_point(struct mtd_info *mtd, loff_t from, size_t len,
	size_t *retlen, void **virt, resource_size_t *phys)
{
	struct map_info *map = mtd->priv;
	*virt = map->virt + from;
	if (phys)
		*phys = map->phys + from;
	*retlen = len;
	return(0);
}

/****************************************************************************/

static int __init ucbeep_mtd_init(void)
{
	struct mtd_info *mtd;
	struct map_info *mapp;

	mapp = &ucbeep_ram_map;
	if (!mapp->size)
		mapp->size = PAGE_ALIGN(ntohl(*((unsigned long *)(mapp->phys + 8))));
	mapp->bankwidth = 4;

	printk("ucbeep[mtd]: RAM probe address=0x%x size=0x%x\n",
	       	(int) mapp->phys, (int) mapp->size);

	/*
	 * The filesystem is guaranteed to be in direct mapped memory. It is
	 * directly following the kernels own bss region. Following the same
	 * mechanism used by architectures setting up traditional initrds we
	 * use phys_to_virt to get the virtual address of its start.
	 */
	mapp->virt = phys_to_virt(mapp->phys);

	if (mapp->virt == 0) {
		printk("ucbeep[mtd]: no virtual mapping?\n");
		return(-EIO);
	}

	simple_map_init(mapp);

	mtd = do_map_probe("map_ram", mapp);
	if (!mtd) {
		printk("ucbeep[mtd]: failed to find a mapping?\n");
		return(-ENXIO);
	}

	mtd->owner = THIS_MODULE;
	mtd->_point = ucbeep_point;
	mtd->priv = mapp;

	ucbeep_ram_mtdinfo = mtd;
	mtd_device_register(mtd, ucbeep_romfs, NUM_PARTITIONS);

	return(0);
}

/****************************************************************************/

static void __exit ucbeep_mtd_cleanup(void)
{
	if (ucbeep_ram_mtdinfo) {
		mtd_device_unregister(ucbeep_ram_mtdinfo);
		map_destroy(ucbeep_ram_mtdinfo);
		ucbeep_ram_mtdinfo = NULL;
	}
	if (ucbeep_ram_map.virt)
		ucbeep_ram_map.virt = 0;
}

/****************************************************************************/

module_init(ucbeep_mtd_init);
module_exit(ucbeep_mtd_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Greg Ungerer <gerg@snapgear.com>");
MODULE_DESCRIPTION("Generic RAM based MTD for uCbeep");

/****************************************************************************/
