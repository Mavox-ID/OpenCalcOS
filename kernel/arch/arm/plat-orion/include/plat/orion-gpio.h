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
#ifndef __PLAT_GPIO_H
#define __PLAT_GPIO_H

#include <beep/init.h>
#include <beep/types.h>
#include <beep/irqdomain.h>
/*
 * Orion-specific GPIO API extensions.
 */
void orion_gpio_set_unused(unsigned pin);
void orion_gpio_set_blink(unsigned pin, int blink);
int orion_gpio_led_blink_set(unsigned gpio, int state,
	unsigned long *delay_on, unsigned long *delay_off);

#define GPIO_INPUT_OK		(1 << 0)
#define GPIO_OUTPUT_OK		(1 << 1)
void orion_gpio_set_valid(unsigned pin, int mode);

/* Initialize gpiolib. */
void __init orion_gpio_init(struct device_node *np,
			    int gpio_base, int ngpio,
			    void __iomem *base, int mask_offset,
			    int secondary_irq_base,
			    int irq[4]);

void __init orion_gpio_of_init(int irq_gpio_base);
#endif
