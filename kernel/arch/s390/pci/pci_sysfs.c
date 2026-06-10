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
#define COMPONENT "zPCI"
#define pr_fmt(fmt) COMPONENT ": " fmt

#include <beep/kernel.h>
#include <beep/stat.h>
#include <beep/pci.h>

static ssize_t show_fid(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct zpci_dev *zdev = get_zdev(container_of(dev, struct pci_dev, dev));

	sprintf(buf, "0x%08x\n", zdev->fid);
	return strlen(buf);
}
static DEVICE_ATTR(function_id, S_IRUGO, show_fid, NULL);

static ssize_t show_fh(struct device *dev, struct device_attribute *attr,
		       char *buf)
{
	struct zpci_dev *zdev = get_zdev(container_of(dev, struct pci_dev, dev));

	sprintf(buf, "0x%08x\n", zdev->fh);
	return strlen(buf);
}
static DEVICE_ATTR(function_handle, S_IRUGO, show_fh, NULL);

static ssize_t show_pchid(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct zpci_dev *zdev = get_zdev(container_of(dev, struct pci_dev, dev));

	sprintf(buf, "0x%04x\n", zdev->pchid);
	return strlen(buf);
}
static DEVICE_ATTR(pchid, S_IRUGO, show_pchid, NULL);

static ssize_t show_pfgid(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct zpci_dev *zdev = get_zdev(container_of(dev, struct pci_dev, dev));

	sprintf(buf, "0x%02x\n", zdev->pfgid);
	return strlen(buf);
}
static DEVICE_ATTR(pfgid, S_IRUGO, show_pfgid, NULL);

static struct device_attribute *zpci_dev_attrs[] = {
	&dev_attr_function_id,
	&dev_attr_function_handle,
	&dev_attr_pchid,
	&dev_attr_pfgid,
	NULL,
};

int zpci_sysfs_add_device(struct device *dev)
{
	int i, rc = 0;

	for (i = 0; zpci_dev_attrs[i]; i++) {
		rc = device_create_file(dev, zpci_dev_attrs[i]);
		if (rc)
			goto error;
	}
	return 0;

error:
	while (--i >= 0)
		device_remove_file(dev, zpci_dev_attrs[i]);
	return rc;
}

void zpci_sysfs_remove_device(struct device *dev)
{
	int i;

	for (i = 0; zpci_dev_attrs[i]; i++)
		device_remove_file(dev, zpci_dev_attrs[i]);
}
