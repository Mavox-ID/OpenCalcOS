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
#include <beep/spinlock.h>
#include <beep/err.h>
#include <asm/types.h>
#include <loongson.h>
#include <beep/gpio.h>

#define STLS2F_N_GPIO		4
#define STLS2F_GPIO_IN_OFFSET	16

static DEFINE_SPINLOCK(gpio_lock);

int gpio_get_value(unsigned gpio)
{
	u32 val;
	u32 mask;

	if (gpio >= STLS2F_N_GPIO)
		return __gpio_get_value(gpio);

	mask = 1 << (gpio + STLS2F_GPIO_IN_OFFSET);
	spin_lock(&gpio_lock);
	val = LOONGSON_GPIODATA;
	spin_unlock(&gpio_lock);

	return ((val & mask) != 0);
}
EXPORT_SYMBOL(gpio_get_value);

void gpio_set_value(unsigned gpio, int state)
{
	u32 val;
	u32 mask;

	if (gpio >= STLS2F_N_GPIO) {
		__gpio_set_value(gpio, state);
		return ;
	}

	mask = 1 << gpio;

	spin_lock(&gpio_lock);
	val = LOONGSON_GPIODATA;
	if (state)
		val |= mask;
	else
		val &= (~mask);
	LOONGSON_GPIODATA = val;
	spin_unlock(&gpio_lock);
}
EXPORT_SYMBOL(gpio_set_value);

int gpio_cansleep(unsigned gpio)
{
	if (gpio < STLS2F_N_GPIO)
		return 0;
	else
		return __gpio_cansleep(gpio);
}
EXPORT_SYMBOL(gpio_cansleep);

static int ls2f_gpio_direction_input(struct gpio_chip *chip, unsigned gpio)
{
	u32 temp;
	u32 mask;

	if (gpio >= STLS2F_N_GPIO)
		return -EINVAL;

	spin_lock(&gpio_lock);
	mask = 1 << gpio;
	temp = LOONGSON_GPIOIE;
	temp |= mask;
	LOONGSON_GPIOIE = temp;
	spin_unlock(&gpio_lock);

	return 0;
}

static int ls2f_gpio_direction_output(struct gpio_chip *chip,
		unsigned gpio, int level)
{
	u32 temp;
	u32 mask;

	if (gpio >= STLS2F_N_GPIO)
		return -EINVAL;

	gpio_set_value(gpio, level);
	spin_lock(&gpio_lock);
	mask = 1 << gpio;
	temp = LOONGSON_GPIOIE;
	temp &= (~mask);
	LOONGSON_GPIOIE = temp;
	spin_unlock(&gpio_lock);

	return 0;
}

static int ls2f_gpio_get_value(struct gpio_chip *chip, unsigned gpio)
{
	return gpio_get_value(gpio);
}

static void ls2f_gpio_set_value(struct gpio_chip *chip,
		unsigned gpio, int value)
{
	gpio_set_value(gpio, value);
}

static struct gpio_chip ls2f_chip = {
	.label                  = "ls2f",
	.direction_input        = ls2f_gpio_direction_input,
	.get                    = ls2f_gpio_get_value,
	.direction_output       = ls2f_gpio_direction_output,
	.set                    = ls2f_gpio_set_value,
	.base                   = 0,
	.ngpio                  = STLS2F_N_GPIO,
};

static int __init ls2f_gpio_setup(void)
{
	return gpiochip_add(&ls2f_chip);
}
arch_initcall(ls2f_gpio_setup);
