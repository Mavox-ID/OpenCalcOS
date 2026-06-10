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
#include <beep/init.h>
#include <beep/module.h>
#include <beep/device.h>
#include <beep/leds.h>

#include <mach/hardware.h>
#include <asm/hardware/locomo.h>

static void locomoled_brightness_set(struct led_classdev *led_cdev,
				enum led_brightness value, int offset)
{
	struct locomo_dev *locomo_dev = LOCOMO_DEV(led_cdev->dev->parent);
	unsigned long flags;

	local_irq_save(flags);
	if (value)
		locomo_writel(LOCOMO_LPT_TOFH, locomo_dev->mapbase + offset);
	else
		locomo_writel(LOCOMO_LPT_TOFL, locomo_dev->mapbase + offset);
	local_irq_restore(flags);
}

static void locomoled_brightness_set0(struct led_classdev *led_cdev,
				enum led_brightness value)
{
	locomoled_brightness_set(led_cdev, value, LOCOMO_LPT0);
}

static void locomoled_brightness_set1(struct led_classdev *led_cdev,
				enum led_brightness value)
{
	locomoled_brightness_set(led_cdev, value, LOCOMO_LPT1);
}

static struct led_classdev locomo_led0 = {
	.name			= "locomo:amber:charge",
	.default_trigger	= "main-battery-charging",
	.brightness_set		= locomoled_brightness_set0,
};

static struct led_classdev locomo_led1 = {
	.name			= "locomo:green:mail",
	.default_trigger	= "nand-disk",
	.brightness_set		= locomoled_brightness_set1,
};

static int locomoled_probe(struct locomo_dev *ldev)
{
	int ret;

	ret = led_classdev_register(&ldev->dev, &locomo_led0);
	if (ret < 0)
		return ret;

	ret = led_classdev_register(&ldev->dev, &locomo_led1);
	if (ret < 0)
		led_classdev_unregister(&locomo_led0);

	return ret;
}

static int locomoled_remove(struct locomo_dev *dev)
{
	led_classdev_unregister(&locomo_led0);
	led_classdev_unregister(&locomo_led1);
	return 0;
}

static struct locomo_driver locomoled_driver = {
	.drv = {
		.name = "locomoled"
	},
	.devid	= LOCOMO_DEVID_LED,
	.probe	= locomoled_probe,
	.remove	= locomoled_remove,
};

static int __init locomoled_init(void)
{
	return locomo_driver_register(&locomoled_driver);
}
module_init(locomoled_init);

MODULE_AUTHOR("John Lenz <lenz@cs.wisc.edu>");
MODULE_DESCRIPTION("Locomo LED driver");
MODULE_LICENSE("GPL");
