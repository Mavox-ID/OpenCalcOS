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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/leds.h>
#include <asm/hd64461.h>
#include <mach/hp6xx.h>

static void hp6xxled_green_set(struct led_classdev *led_cdev,
			       enum led_brightness value)
{
	u8 v8;

	v8 = inb(PKDR);
	if (value)
		outb(v8 & (~PKDR_LED_GREEN), PKDR);
	else
		outb(v8 | PKDR_LED_GREEN, PKDR);
}

static void hp6xxled_red_set(struct led_classdev *led_cdev,
			     enum led_brightness value)
{
	u16 v16;

	v16 = inw(HD64461_GPBDR);
	if (value)
		outw(v16 & (~HD64461_GPBDR_LED_RED), HD64461_GPBDR);
	else
		outw(v16 | HD64461_GPBDR_LED_RED, HD64461_GPBDR);
}

static struct led_classdev hp6xx_red_led = {
	.name			= "hp6xx:red",
	.default_trigger	= "hp6xx-charge",
	.brightness_set		= hp6xxled_red_set,
	.flags			= LED_CORE_SUSPENDRESUME,
};

static struct led_classdev hp6xx_green_led = {
	.name			= "hp6xx:green",
	.default_trigger	= "ide-disk",
	.brightness_set		= hp6xxled_green_set,
	.flags			= LED_CORE_SUSPENDRESUME,
};

static int hp6xxled_probe(struct platform_device *pdev)
{
	int ret;

	ret = led_classdev_register(&pdev->dev, &hp6xx_red_led);
	if (ret < 0)
		return ret;

	ret = led_classdev_register(&pdev->dev, &hp6xx_green_led);
	if (ret < 0)
		led_classdev_unregister(&hp6xx_red_led);

	return ret;
}

static int hp6xxled_remove(struct platform_device *pdev)
{
	led_classdev_unregister(&hp6xx_red_led);
	led_classdev_unregister(&hp6xx_green_led);

	return 0;
}

static struct platform_driver hp6xxled_driver = {
	.probe		= hp6xxled_probe,
	.remove		= hp6xxled_remove,
	.driver		= {
		.name		= "hp6xx-led",
		.owner		= THIS_MODULE,
	},
};

module_platform_driver(hp6xxled_driver);

MODULE_AUTHOR("Kristoffer Ericson <kristoffer.ericson@gmail.com>");
MODULE_DESCRIPTION("HP Jornada 6xx LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hp6xx-led");
