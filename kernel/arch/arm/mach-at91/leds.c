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
#include <beep/gpio.h>
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/init.h>
#include <beep/platform_device.h>

#include "board.h"


/* ------------------------------------------------------------------------- */

#if defined(CONFIG_NEW_LEDS)

/*
 * New cross-platform LED support.
 */

static struct gpio_led_platform_data led_data;

static struct platform_device at91_gpio_leds_device = {
	.name			= "leds-gpio",
	.id			= -1,
	.dev.platform_data	= &led_data,
};

void __init at91_gpio_leds(struct gpio_led *leds, int nr)
{
	int i;

	if (!nr)
		return;

	for (i = 0; i < nr; i++)
		at91_set_gpio_output(leds[i].gpio, leds[i].active_low);

	led_data.leds = leds;
	led_data.num_leds = nr;
	platform_device_register(&at91_gpio_leds_device);
}

#else
void __init at91_gpio_leds(struct gpio_led *leds, int nr) {}
#endif


/* ------------------------------------------------------------------------- */

#if defined (CONFIG_LEDS_ATMEL_PWM)

/*
 * PWM Leds
 */

static struct gpio_led_platform_data pwm_led_data;

static struct platform_device at91_pwm_leds_device = {
	.name			= "leds-atmel-pwm",
	.id			= -1,
	.dev.platform_data	= &pwm_led_data,
};

void __init at91_pwm_leds(struct gpio_led *leds, int nr)
{
	int i;
	u32 pwm_mask = 0;

	if (!nr)
		return;

	for (i = 0; i < nr; i++)
		pwm_mask |= (1 << leds[i].gpio);

	pwm_led_data.leds = leds;
	pwm_led_data.num_leds = nr;

	at91_add_device_pwm(pwm_mask);
	platform_device_register(&at91_pwm_leds_device);
}
#else
void __init at91_pwm_leds(struct gpio_led *leds, int nr){}
#endif
