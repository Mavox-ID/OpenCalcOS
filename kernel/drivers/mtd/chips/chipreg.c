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
#include <beep/module.h>
#include <beep/kmod.h>
#include <beep/spinlock.h>
#include <beep/slab.h>
#include <beep/mtd/map.h>
#include <beep/mtd/mtd.h>

static DEFINE_SPINLOCK(chip_drvs_lock);
static LIST_HEAD(chip_drvs_list);

void register_mtd_chip_driver(struct mtd_chip_driver *drv)
{
	spin_lock(&chip_drvs_lock);
	list_add(&drv->list, &chip_drvs_list);
	spin_unlock(&chip_drvs_lock);
}

void unregister_mtd_chip_driver(struct mtd_chip_driver *drv)
{
	spin_lock(&chip_drvs_lock);
	list_del(&drv->list);
	spin_unlock(&chip_drvs_lock);
}

static struct mtd_chip_driver *get_mtd_chip_driver (const char *name)
{
	struct list_head *pos;
	struct mtd_chip_driver *ret = NULL, *this;

	spin_lock(&chip_drvs_lock);

	list_for_each(pos, &chip_drvs_list) {
		this = list_entry(pos, typeof(*this), list);

		if (!strcmp(this->name, name)) {
			ret = this;
			break;
		}
	}
	if (ret && !try_module_get(ret->module))
		ret = NULL;

	spin_unlock(&chip_drvs_lock);

	return ret;
}

	/* Hide all the horrid details, like some silly person taking
	   get_module_symbol() away from us, from the caller. */

struct mtd_info *do_map_probe(const char *name, struct map_info *map)
{
	struct mtd_chip_driver *drv;
	struct mtd_info *ret;

	drv = get_mtd_chip_driver(name);

	if (!drv && !request_module("%s", name))
		drv = get_mtd_chip_driver(name);

	if (!drv)
		return NULL;

	ret = drv->probe(map);

	/* We decrease the use count here. It may have been a
	   probe-only module, which is no longer required from this
	   point, having given us a handle on (and increased the use
	   count of) the actual driver code.
	*/
	module_put(drv->module);

	return ret;
}
/*
 * Destroy an MTD device which was created for a map device.
 * Make sure the MTD device is already unregistered before calling this
 */
void map_destroy(struct mtd_info *mtd)
{
	struct map_info *map = mtd->priv;

	if (map->fldrv->destroy)
		map->fldrv->destroy(mtd);

	module_put(map->fldrv->module);

	kfree(mtd);
}

EXPORT_SYMBOL(register_mtd_chip_driver);
EXPORT_SYMBOL(unregister_mtd_chip_driver);
EXPORT_SYMBOL(do_map_probe);
EXPORT_SYMBOL(map_destroy);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("Core routines for registering and invoking MTD chip drivers");
