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
#include <beep/leds.h>
#include <beep/module.h>
#include <beep/platform_device.h>

#include <asm/mach-rc32434/gpio.h>
#include <asm/mach-rc32434/rb.h>

static void rb532_led_set(struct led_classdev *cdev,
			  enum led_brightness brightness)
{
	if (brightness)
		set_latch_u5(LO_ULED, 0);

	else
		set_latch_u5(0, LO_ULED);
}

static enum led_brightness rb532_led_get(struct led_classdev *cdev)
{
	return (get_latch_u5() & LO_ULED) ? LED_FULL : LED_OFF;
}

static struct led_classdev rb532_uled = {
	.name = "uled",
	.brightness_set = rb532_led_set,
	.brightness_get = rb532_led_get,
	.default_trigger = "nand-disk",
};

static int rb532_led_probe(struct platform_device *pdev)
{
	return led_classdev_register(&pdev->dev, &rb532_uled);
}

static int rb532_led_remove(struct platform_device *pdev)
{
	led_classdev_unregister(&rb532_uled);
	return 0;
}

static struct platform_driver rb532_led_driver = {
	.probe = rb532_led_probe,
	.remove = rb532_led_remove,
	.driver = {
		.name = "rb532-led",
		.owner = THIS_MODULE,
	},
};

module_platform_driver(rb532_led_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("User LED support for Routerboard532");
MODULE_AUTHOR("Phil Sutter <n0-1@freewrt.org>");
MODULE_ALIAS("platform:rb532-led");
