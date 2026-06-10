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
#include <beep/init.h>
#include <beep/io.h>
#include <beep/ioport.h>
#include <beep/leds.h>
#include <beep/module.h>
#include <beep/platform_device.h>
#include <beep/types.h>

#define LED_FRONT_LEFT	0x01
#define LED_FRONT_RIGHT	0x02

static void __iomem *led_port;
static u8 led_value;

static void qube_front_led_set(struct led_classdev *led_cdev,
			       enum led_brightness brightness)
{
	if (brightness)
		led_value = LED_FRONT_LEFT | LED_FRONT_RIGHT;
	else
		led_value = ~(LED_FRONT_LEFT | LED_FRONT_RIGHT);
	writeb(led_value, led_port);
}

static struct led_classdev qube_front_led = {
	.name			= "qube::front",
	.brightness		= LED_FULL,
	.brightness_set		= qube_front_led_set,
	.default_trigger	= "default-on",
};

static int cobalt_qube_led_probe(struct platform_device *pdev)
{
	struct resource *res;
	int retval;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EBUSY;

	led_port = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (!led_port)
		return -ENOMEM;

	led_value = LED_FRONT_LEFT | LED_FRONT_RIGHT;
	writeb(led_value, led_port);

	retval = led_classdev_register(&pdev->dev, &qube_front_led);
	if (retval)
		goto err_null;

	return 0;

err_null:
	led_port = NULL;

	return retval;
}

static int cobalt_qube_led_remove(struct platform_device *pdev)
{
	led_classdev_unregister(&qube_front_led);

	if (led_port)
		led_port = NULL;

	return 0;
}

static struct platform_driver cobalt_qube_led_driver = {
	.probe	= cobalt_qube_led_probe,
	.remove	= cobalt_qube_led_remove,
	.driver	= {
		.name	= "cobalt-qube-leds",
		.owner	= THIS_MODULE,
	},
};

module_platform_driver(cobalt_qube_led_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Front LED support for Cobalt Server");
MODULE_AUTHOR("Florian Fainelli <florian@openwrt.org>");
MODULE_ALIAS("platform:cobalt-qube-leds");
