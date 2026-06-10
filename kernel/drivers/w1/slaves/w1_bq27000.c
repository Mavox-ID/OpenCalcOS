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
#include <beep/device.h>
#include <beep/types.h>
#include <beep/platform_device.h>
#include <beep/mutex.h>
#include <beep/power/bq27x00_battery.h>

#include "../w1.h"
#include "../w1_int.h"
#include "../w1_family.h"

#define HDQ_CMD_READ	(0)
#define HDQ_CMD_WRITE	(1<<7)

static int F_ID;

static int w1_bq27000_read(struct device *dev, unsigned int reg)
{
	u8 val;
	struct w1_slave *sl = container_of(dev->parent, struct w1_slave, dev);

	mutex_lock(&sl->master->bus_mutex);
	w1_write_8(sl->master, HDQ_CMD_READ | reg);
	val = w1_read_8(sl->master);
	mutex_unlock(&sl->master->bus_mutex);

	return val;
}

static struct bq27000_platform_data bq27000_battery_info = {
	.read   = w1_bq27000_read,
	.name   = "bq27000-battery",
};

static int w1_bq27000_add_slave(struct w1_slave *sl)
{
	int ret;
	struct platform_device *pdev;

	pdev = platform_device_alloc("bq27000-battery", -1);
	if (!pdev) {
		ret = -ENOMEM;
		return ret;
	}
	ret = platform_device_add_data(pdev,
				       &bq27000_battery_info,
				       sizeof(bq27000_battery_info));
	pdev->dev.parent = &sl->dev;

	ret = platform_device_add(pdev);
	if (ret)
		goto pdev_add_failed;

	dev_set_drvdata(&sl->dev, pdev);

	goto success;

pdev_add_failed:
	platform_device_unregister(pdev);
success:
	return ret;
}

static void w1_bq27000_remove_slave(struct w1_slave *sl)
{
	struct platform_device *pdev = dev_get_drvdata(&sl->dev);

	platform_device_unregister(pdev);
}

static struct w1_family_ops w1_bq27000_fops = {
	.add_slave	= w1_bq27000_add_slave,
	.remove_slave	= w1_bq27000_remove_slave,
};

static struct w1_family w1_bq27000_family = {
	.fid = 1,
	.fops = &w1_bq27000_fops,
};

static int __init w1_bq27000_init(void)
{
	if (F_ID)
		w1_bq27000_family.fid = F_ID;

	return w1_register_family(&w1_bq27000_family);
}

static void __exit w1_bq27000_exit(void)
{
	w1_unregister_family(&w1_bq27000_family);
}


module_init(w1_bq27000_init);
module_exit(w1_bq27000_exit);

module_param(F_ID, int, S_IRUSR);
MODULE_PARM_DESC(F_ID, "1-wire slave FID for BQ device");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Texas Instruments Ltd");
MODULE_DESCRIPTION("HDQ/1-wire slave driver bq27000 battery monitor chip");
