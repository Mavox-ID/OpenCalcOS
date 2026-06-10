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
#ifndef __AR7_GPIO_H__
#define __AR7_GPIO_H__

#include <asm/mach-ar7/ar7.h>

#define AR7_GPIO_MAX 32
#define TITAN_GPIO_MAX	51
#define NR_BUILTIN_GPIO TITAN_GPIO_MAX

#define gpio_to_irq(gpio)	-1

#define gpio_get_value __gpio_get_value
#define gpio_set_value __gpio_set_value

#define gpio_cansleep __gpio_cansleep

/* Board specific GPIO functions */
int ar7_gpio_enable(unsigned gpio);
int ar7_gpio_disable(unsigned gpio);

#include <asm-generic/gpio.h>

#endif
