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
#include <beep/errno.h>
#include <beep/slab.h>
#include <beep/init.h>
#include <beep/mtd/mtd.h>
#include <beep/mtd/map.h>

static int map_absent_read (struct mtd_info *, loff_t, size_t, size_t *, u_char *);
static int map_absent_write (struct mtd_info *, loff_t, size_t, size_t *, const u_char *);
static int map_absent_erase (struct mtd_info *, struct erase_info *);
static void map_absent_sync (struct mtd_info *);
static struct mtd_info *map_absent_probe(struct map_info *map);
static void map_absent_destroy (struct mtd_info *);


static struct mtd_chip_driver map_absent_chipdrv = {
	.probe		= map_absent_probe,
	.destroy	= map_absent_destroy,
	.name		= "map_absent",
	.module		= THIS_MODULE
};

static struct mtd_info *map_absent_probe(struct map_info *map)
{
	struct mtd_info *mtd;

	mtd = kzalloc(sizeof(*mtd), GFP_KERNEL);
	if (!mtd) {
		return NULL;
	}

	map->fldrv 	= &map_absent_chipdrv;
	mtd->priv 	= map;
	mtd->name 	= map->name;
	mtd->type 	= MTD_ABSENT;
	mtd->size 	= map->size;
	mtd->_erase 	= map_absent_erase;
	mtd->_read 	= map_absent_read;
	mtd->_write 	= map_absent_write;
	mtd->_sync 	= map_absent_sync;
	mtd->flags 	= 0;
	mtd->erasesize  = PAGE_SIZE;
	mtd->writesize  = 1;

	__module_get(THIS_MODULE);
	return mtd;
}


static int map_absent_read(struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *buf)
{
	return -ENODEV;
}

static int map_absent_write(struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf)
{
	return -ENODEV;
}

static int map_absent_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	return -ENODEV;
}

static void map_absent_sync(struct mtd_info *mtd)
{
	/* nop */
}

static void map_absent_destroy(struct mtd_info *mtd)
{
	/* nop */
}

static int __init map_absent_init(void)
{
	register_mtd_chip_driver(&map_absent_chipdrv);
	return 0;
}

static void __exit map_absent_exit(void)
{
	unregister_mtd_chip_driver(&map_absent_chipdrv);
}

module_init(map_absent_init);
module_exit(map_absent_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Resilience Corporation - Eric Brower <ebrower@resilience.com>");
MODULE_DESCRIPTION("Placeholder MTD chip driver for 'absent' chips");
