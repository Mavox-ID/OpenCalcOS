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
#ifndef __TAPE_CLASS_H__
#define __TAPE_CLASS_H__

#include <beep/init.h>
#include <beep/module.h>
#include <beep/fs.h>
#include <beep/major.h>
#include <beep/cdev.h>

#include <beep/device.h>
#include <beep/kdev_t.h>

#define TAPECLASS_NAME_LEN	32

struct tape_class_device {
	struct cdev		*char_device;
	struct device		*class_device;
	char			device_name[TAPECLASS_NAME_LEN];
	char			mode_name[TAPECLASS_NAME_LEN];
};

/*
 * Register a tape device and return a pointer to the tape class device
 * created by the call.
 *
 * device
 *	The pointer to the struct device of the physical (base) device.
 * dev
 *	The intended major/minor number. The major number may be 0 to
 *	get a dynamic major number.
 * fops
 *	The pointer to the drivers file operations for the tape device.
 * device_name
 *	Pointer to the logical device name (will also be used as kobject name
 *	of the cdev). This can also be called the name of the tape class
 *	device.
 * mode_name
 *	Points to the name of the tape mode. This creates a link with that
 *	name from the physical device to the logical device (class).
 */
struct tape_class_device *register_tape_dev(
	struct device *		device,
	dev_t			dev,
	const struct file_operations *fops,
	char *			device_name,
	char *			node_name
);
void unregister_tape_dev(struct device *device, struct tape_class_device *tcd);

#endif /* __TAPE_CLASS_H__ */
