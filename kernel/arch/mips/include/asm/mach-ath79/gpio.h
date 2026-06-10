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
#ifndef __ASM_MACH_ATH79_GPIO_H
#define __ASM_MACH_ATH79_GPIO_H

#define ARCH_NR_GPIOS	64
#include <asm-generic/gpio.h>

int gpio_to_irq(unsigned gpio);
int irq_to_gpio(unsigned irq);
int gpio_get_value(unsigned gpio);
void gpio_set_value(unsigned gpio, int value);

#define gpio_cansleep	__gpio_cansleep

#endif /* __ASM_MACH_ATH79_GPIO_H */
