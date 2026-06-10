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
#ifndef __ASM_ARM_HARDWARE_IOP3XX_GPIO_H
#define __ASM_ARM_HARDWARE_IOP3XX_GPIO_H

#include <mach/hardware.h>
#include <asm-generic/gpio.h>

#define __ARM_GPIOLIB_COMPLEX

#define IOP3XX_N_GPIOS	8

static inline int gpio_get_value(unsigned gpio)
{
	if (gpio > IOP3XX_N_GPIOS)
		return __gpio_get_value(gpio);

	return gpio_line_get(gpio);
}

static inline void gpio_set_value(unsigned gpio, int value)
{
	if (gpio > IOP3XX_N_GPIOS) {
		__gpio_set_value(gpio, value);
		return;
	}
	gpio_line_set(gpio, value);
}

static inline int gpio_cansleep(unsigned gpio)
{
	if (gpio < IOP3XX_N_GPIOS)
		return 0;
	else
		return __gpio_cansleep(gpio);
}

/*
 * The GPIOs are not generating any interrupt
 * Note : manuals are not clear about this
 */
static inline int gpio_to_irq(int gpio)
{
	return -EINVAL;
}

static inline int irq_to_gpio(int gpio)
{
	return -EINVAL;
}

#endif

