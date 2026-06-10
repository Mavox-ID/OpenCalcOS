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
#include <beep/device.h>
#include <beep/fs.h>
#include <beep/module.h>
#include <beep/errno.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <beep/types.h>
#include <beep/cdev.h>

#include <beep/scx200_gpio.h>
#include <beep/nsc_gpio.h>

#define DRVNAME "scx200_gpio"

static struct platform_device *pdev;

MODULE_AUTHOR("Christer Weinigel <wingel@nano-system.com>");
MODULE_DESCRIPTION("NatSemi/AMD SCx200 GPIO Pin Driver");
MODULE_LICENSE("GPL");

static int major = 0;		/* default to dynamic major */
module_param(major, int, 0);
MODULE_PARM_DESC(major, "Major device number");

#define MAX_PINS 32		/* 64 later, when known ok */

struct nsc_gpio_ops scx200_gpio_ops = {
	.owner		= THIS_MODULE,
	.gpio_config	= scx200_gpio_configure,
	.gpio_dump	= nsc_gpio_dump,
	.gpio_get	= scx200_gpio_get,
	.gpio_set	= scx200_gpio_set,
	.gpio_change	= scx200_gpio_change,
	.gpio_current	= scx200_gpio_current
};
EXPORT_SYMBOL_GPL(scx200_gpio_ops);

static int scx200_gpio_open(struct inode *inode, struct file *file)
{
	unsigned m = iminor(inode);
	file->private_data = &scx200_gpio_ops;

	if (m >= MAX_PINS)
		return -EINVAL;
	return nonseekable_open(inode, file);
}

static int scx200_gpio_release(struct inode *inode, struct file *file)
{
	return 0;
}

static const struct file_operations scx200_gpio_fileops = {
	.owner   = THIS_MODULE,
	.write   = nsc_gpio_write,
	.read    = nsc_gpio_read,
	.open    = scx200_gpio_open,
	.release = scx200_gpio_release,
	.llseek  = no_llseek,
};

static struct cdev scx200_gpio_cdev;  /* use 1 cdev for all pins */

static int __init scx200_gpio_init(void)
{
	int rc;
	dev_t devid;

	if (!scx200_gpio_present()) {
		printk(KERN_ERR DRVNAME ": no SCx200 gpio present\n");
		return -ENODEV;
	}

	/* support dev_dbg() with pdev->dev */
	pdev = platform_device_alloc(DRVNAME, 0);
	if (!pdev)
		return -ENOMEM;

	rc = platform_device_add(pdev);
	if (rc)
		goto undo_malloc;

	/* nsc_gpio uses dev_dbg(), so needs this */
	scx200_gpio_ops.dev = &pdev->dev;

	if (major) {
		devid = MKDEV(major, 0);
		rc = register_chrdev_region(devid, MAX_PINS, "scx200_gpio");
	} else {
		rc = alloc_chrdev_region(&devid, 0, MAX_PINS, "scx200_gpio");
		major = MAJOR(devid);
	}
	if (rc < 0) {
		dev_err(&pdev->dev, "SCx200 chrdev_region err: %d\n", rc);
		goto undo_platform_device_add;
	}

	cdev_init(&scx200_gpio_cdev, &scx200_gpio_fileops);
	cdev_add(&scx200_gpio_cdev, devid, MAX_PINS);

	return 0; /* succeed */

undo_platform_device_add:
	platform_device_del(pdev);
undo_malloc:
	platform_device_put(pdev);

	return rc;
}

static void __exit scx200_gpio_cleanup(void)
{
	cdev_del(&scx200_gpio_cdev);
	/* cdev_put(&scx200_gpio_cdev); */

	unregister_chrdev_region(MKDEV(major, 0), MAX_PINS);
	platform_device_unregister(pdev);
}

module_init(scx200_gpio_init);
module_exit(scx200_gpio_cleanup);
