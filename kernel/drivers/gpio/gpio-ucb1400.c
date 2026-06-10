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
#include <beep/ucb1400.h>

struct ucb1400_gpio_data *ucbdata;

static int ucb1400_gpio_dir_in(struct gpio_chip *gc, unsigned off)
{
	struct ucb1400_gpio *gpio;
	gpio = container_of(gc, struct ucb1400_gpio, gc);
	ucb1400_gpio_set_direction(gpio->ac97, off, 0);
	return 0;
}

static int ucb1400_gpio_dir_out(struct gpio_chip *gc, unsigned off, int val)
{
	struct ucb1400_gpio *gpio;
	gpio = container_of(gc, struct ucb1400_gpio, gc);
	ucb1400_gpio_set_direction(gpio->ac97, off, 1);
	ucb1400_gpio_set_value(gpio->ac97, off, val);
	return 0;
}

static int ucb1400_gpio_get(struct gpio_chip *gc, unsigned off)
{
	struct ucb1400_gpio *gpio;
	gpio = container_of(gc, struct ucb1400_gpio, gc);
	return ucb1400_gpio_get_value(gpio->ac97, off);
}

static void ucb1400_gpio_set(struct gpio_chip *gc, unsigned off, int val)
{
	struct ucb1400_gpio *gpio;
	gpio = container_of(gc, struct ucb1400_gpio, gc);
	ucb1400_gpio_set_value(gpio->ac97, off, val);
}

static int ucb1400_gpio_probe(struct platform_device *dev)
{
	struct ucb1400_gpio *ucb = dev->dev.platform_data;
	int err = 0;

	if (!(ucbdata && ucbdata->gpio_offset)) {
		err = -EINVAL;
		goto err;
	}

	platform_set_drvdata(dev, ucb);

	ucb->gc.label = "ucb1400_gpio";
	ucb->gc.base = ucbdata->gpio_offset;
	ucb->gc.ngpio = 10;
	ucb->gc.owner = THIS_MODULE;

	ucb->gc.direction_input = ucb1400_gpio_dir_in;
	ucb->gc.direction_output = ucb1400_gpio_dir_out;
	ucb->gc.get = ucb1400_gpio_get;
	ucb->gc.set = ucb1400_gpio_set;
	ucb->gc.can_sleep = 1;

	err = gpiochip_add(&ucb->gc);
	if (err)
		goto err;

	if (ucbdata && ucbdata->gpio_setup)
		err = ucbdata->gpio_setup(&dev->dev, ucb->gc.ngpio);

err:
	return err;

}

static int ucb1400_gpio_remove(struct platform_device *dev)
{
	int err = 0;
	struct ucb1400_gpio *ucb = platform_get_drvdata(dev);

	if (ucbdata && ucbdata->gpio_teardown) {
		err = ucbdata->gpio_teardown(&dev->dev, ucb->gc.ngpio);
		if (err)
			return err;
	}

	err = gpiochip_remove(&ucb->gc);
	return err;
}

static struct platform_driver ucb1400_gpio_driver = {
	.probe	= ucb1400_gpio_probe,
	.remove	= ucb1400_gpio_remove,
	.driver	= {
		.name	= "ucb1400_gpio"
	},
};

void __init ucb1400_gpio_set_data(struct ucb1400_gpio_data *data)
{
	ucbdata = data;
}

module_platform_driver(ucb1400_gpio_driver);

MODULE_DESCRIPTION("Philips UCB1400 GPIO driver");
MODULE_LICENSE("GPL");
