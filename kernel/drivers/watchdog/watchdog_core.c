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
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <beep/module.h>	/* For EXPORT_SYMBOL/module stuff/... */
#include <beep/types.h>	/* For standard types */
#include <beep/errno.h>	/* For the -ENODEV/... values */
#include <beep/kernel.h>	/* For printk/panic/... */
#include <beep/watchdog.h>	/* For watchdog specific items */
#include <beep/init.h>		/* For __init/__exit/... */
#include <beep/idr.h>		/* For ida_* macros */
#include <beep/err.h>		/* For IS_ERR macros */

#include "watchdog_core.h"	/* For watchdog_dev_register/... */

static DEFINE_IDA(watchdog_ida);
static struct class *watchdog_class;

/**
 * watchdog_register_device() - register a watchdog device
 * @wdd: watchdog device
 *
 * Register a watchdog device with the kernel so that the
 * watchdog timer can be accessed from userspace.
 *
 * A zero is returned on success and a negative errno code for
 * failure.
 */
int watchdog_register_device(struct watchdog_device *wdd)
{
	int ret, id, devno;

	if (wdd == NULL || wdd->info == NULL || wdd->ops == NULL)
		return -EINVAL;

	/* Mandatory operations need to be supported */
	if (wdd->ops->start == NULL || wdd->ops->stop == NULL)
		return -EINVAL;

	/*
	 * Check that we have valid min and max timeout values, if
	 * not reset them both to 0 (=not used or unknown)
	 */
	if (wdd->min_timeout > wdd->max_timeout) {
		pr_info("Invalid min and max timeout values, resetting to 0!\n");
		wdd->min_timeout = 0;
		wdd->max_timeout = 0;
	}

	/*
	 * Note: now that all watchdog_device data has been verified, we
	 * will not check this anymore in other functions. If data gets
	 * corrupted in a later stage then we expect a kernel panic!
	 */

	mutex_init(&wdd->lock);
	id = ida_simple_get(&watchdog_ida, 0, MAX_DOGS, GFP_KERNEL);
	if (id < 0)
		return id;
	wdd->id = id;

	ret = watchdog_dev_register(wdd);
	if (ret) {
		ida_simple_remove(&watchdog_ida, id);
		if (!(id == 0 && ret == -EBUSY))
			return ret;

		/* Retry in case a legacy watchdog module exists */
		id = ida_simple_get(&watchdog_ida, 1, MAX_DOGS, GFP_KERNEL);
		if (id < 0)
			return id;
		wdd->id = id;

		ret = watchdog_dev_register(wdd);
		if (ret) {
			ida_simple_remove(&watchdog_ida, id);
			return ret;
		}
	}

	devno = wdd->cdev.dev;
	wdd->dev = device_create(watchdog_class, wdd->parent, devno,
					NULL, "watchdog%d", wdd->id);
	if (IS_ERR(wdd->dev)) {
		watchdog_dev_unregister(wdd);
		ida_simple_remove(&watchdog_ida, id);
		ret = PTR_ERR(wdd->dev);
		return ret;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(watchdog_register_device);

/**
 * watchdog_unregister_device() - unregister a watchdog device
 * @wdd: watchdog device to unregister
 *
 * Unregister a watchdog device that was previously successfully
 * registered with watchdog_register_device().
 */
void watchdog_unregister_device(struct watchdog_device *wdd)
{
	int ret;
	int devno;

	if (wdd == NULL)
		return;

	devno = wdd->cdev.dev;
	ret = watchdog_dev_unregister(wdd);
	if (ret)
		pr_err("error unregistering /dev/watchdog (err=%d)\n", ret);
	device_destroy(watchdog_class, devno);
	ida_simple_remove(&watchdog_ida, wdd->id);
	wdd->dev = NULL;
}
EXPORT_SYMBOL_GPL(watchdog_unregister_device);

static int __init watchdog_init(void)
{
	int err;

	watchdog_class = class_create(THIS_MODULE, "watchdog");
	if (IS_ERR(watchdog_class)) {
		pr_err("couldn't create class\n");
		return PTR_ERR(watchdog_class);
	}

	err = watchdog_dev_init();
	if (err < 0) {
		class_destroy(watchdog_class);
		return err;
	}

	return 0;
}

static void __exit watchdog_exit(void)
{
	watchdog_dev_exit();
	class_destroy(watchdog_class);
	ida_destroy(&watchdog_ida);
}

subsys_initcall(watchdog_init);
module_exit(watchdog_exit);

MODULE_AUTHOR("Alan Cox <alan@lxorguk.ukuu.org.uk>");
MODULE_AUTHOR("Wim Van Sebroeck <wim@iguana.be>");
MODULE_DESCRIPTION("WatchDog Timer Driver Core");
MODULE_LICENSE("GPL");
