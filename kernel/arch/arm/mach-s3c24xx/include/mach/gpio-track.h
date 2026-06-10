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
#ifndef __ASM_ARCH_GPIO_CORE_H
#define __ASM_ARCH_GPIO_CORE_H __FILE__

#include <mach/regs-gpio.h>

extern struct samsung_gpio_chip s3c24xx_gpios[];

static inline struct samsung_gpio_chip *samsung_gpiolib_getchip(unsigned int pin)
{
	struct samsung_gpio_chip *chip;

	if (pin > S3C_GPIO_END)
		return NULL;

	chip = &s3c24xx_gpios[pin/32];
	return ((pin - chip->chip.base) < chip->chip.ngpio) ? chip : NULL;
}

#endif /* __ASM_ARCH_GPIO_CORE_H */
