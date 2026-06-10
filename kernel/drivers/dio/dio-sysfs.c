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
#include <beep/dio.h>
#include <beep/stat.h>

/* show configuration fields */

static ssize_t dio_show_id(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct dio_dev *d;

	d = to_dio_dev(dev);
	return sprintf(buf, "0x%02x\n", (d->id & 0xff));
}
static DEVICE_ATTR(id, S_IRUGO, dio_show_id, NULL);

static ssize_t dio_show_ipl(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct dio_dev *d;

	d = to_dio_dev(dev);
	return sprintf(buf, "0x%02x\n", d->ipl);
}
static DEVICE_ATTR(ipl, S_IRUGO, dio_show_ipl, NULL);

static ssize_t dio_show_secid(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct dio_dev *d;

	d = to_dio_dev(dev);
	return sprintf(buf, "0x%02x\n", ((d->id >> 8)& 0xff));
}
static DEVICE_ATTR(secid, S_IRUGO, dio_show_secid, NULL);

static ssize_t dio_show_name(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct dio_dev *d;

	d = to_dio_dev(dev);
	return sprintf(buf, "%s\n", d->name);
}
static DEVICE_ATTR(name, S_IRUGO, dio_show_name, NULL);

static ssize_t dio_show_resource(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct dio_dev *d = to_dio_dev(dev);

	return sprintf(buf, "0x%08lx 0x%08lx 0x%08lx\n",
		       (unsigned long)dio_resource_start(d),
		       (unsigned long)dio_resource_end(d),
		       dio_resource_flags(d));
}
static DEVICE_ATTR(resource, S_IRUGO, dio_show_resource, NULL);

int dio_create_sysfs_dev_files(struct dio_dev *d)
{
	struct device *dev = &d->dev;
	int error;

	/* current configuration's attributes */
	if ((error = device_create_file(dev, &dev_attr_id)) ||
	    (error = device_create_file(dev, &dev_attr_ipl)) ||
	    (error = device_create_file(dev, &dev_attr_secid)) ||
	    (error = device_create_file(dev, &dev_attr_name)) ||
	    (error = device_create_file(dev, &dev_attr_resource)))
		return error;

	return 0;
}

