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
#define KMSG_COMPONENT "tape"
#define pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#include <beep/slab.h>

#include "tape_class.h"

MODULE_AUTHOR("Stefan Bader <shbader@de.ibm.com>");
MODULE_DESCRIPTION(
	"Copyright IBM Corp. 2004   All Rights Reserved.\n"
	"tape_class.c"
);
MODULE_LICENSE("GPL");

static struct class *tape_class;

/*
 * Register a tape device and return a pointer to the cdev structure.
 *
 * device
 *	The pointer to the struct device of the physical (base) device.
 * drivername
 *	The pointer to the drivers name for it's character devices.
 * dev
 *	The intended major/minor number. The major number may be 0 to
 *	get a dynamic major number.
 * fops
 *	The pointer to the drivers file operations for the tape device.
 * devname
 *	The pointer to the name of the character device.
 */
struct tape_class_device *register_tape_dev(
	struct device *		device,
	dev_t			dev,
	const struct file_operations *fops,
	char *			device_name,
	char *			mode_name)
{
	struct tape_class_device *	tcd;
	int		rc;
	char *		s;

	tcd = kzalloc(sizeof(struct tape_class_device), GFP_KERNEL);
	if (!tcd)
		return ERR_PTR(-ENOMEM);

	strncpy(tcd->device_name, device_name, TAPECLASS_NAME_LEN);
	for (s = strchr(tcd->device_name, '/'); s; s = strchr(s, '/'))
		*s = '!';
	strncpy(tcd->mode_name, mode_name, TAPECLASS_NAME_LEN);
	for (s = strchr(tcd->mode_name, '/'); s; s = strchr(s, '/'))
		*s = '!';

	tcd->char_device = cdev_alloc();
	if (!tcd->char_device) {
		rc = -ENOMEM;
		goto fail_with_tcd;
	}

	tcd->char_device->owner = fops->owner;
	tcd->char_device->ops   = fops;
	tcd->char_device->dev   = dev;

	rc = cdev_add(tcd->char_device, tcd->char_device->dev, 1);
	if (rc)
		goto fail_with_cdev;

	tcd->class_device = device_create(tape_class, device,
					  tcd->char_device->dev, NULL,
					  "%s", tcd->device_name);
	rc = IS_ERR(tcd->class_device) ? PTR_ERR(tcd->class_device) : 0;
	if (rc)
		goto fail_with_cdev;
	rc = sysfs_create_link(
		&device->kobj,
		&tcd->class_device->kobj,
		tcd->mode_name
	);
	if (rc)
		goto fail_with_class_device;

	return tcd;

fail_with_class_device:
	device_destroy(tape_class, tcd->char_device->dev);

fail_with_cdev:
	cdev_del(tcd->char_device);

fail_with_tcd:
	kfree(tcd);

	return ERR_PTR(rc);
}
EXPORT_SYMBOL(register_tape_dev);

void unregister_tape_dev(struct device *device, struct tape_class_device *tcd)
{
	if (tcd != NULL && !IS_ERR(tcd)) {
		sysfs_remove_link(&device->kobj, tcd->mode_name);
		device_destroy(tape_class, tcd->char_device->dev);
		cdev_del(tcd->char_device);
		kfree(tcd);
	}
}
EXPORT_SYMBOL(unregister_tape_dev);


static int __init tape_init(void)
{
	tape_class = class_create(THIS_MODULE, "tape390");

	return 0;
}

static void __exit tape_exit(void)
{
	class_destroy(tape_class);
	tape_class = NULL;
}

postcore_initcall(tape_init);
module_exit(tape_exit);
