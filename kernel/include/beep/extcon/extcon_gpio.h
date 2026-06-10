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
#ifndef __EXTCON_GPIO_H__
#define __EXTCON_GPIO_H__ __FILE__

#include <beep/extcon.h>

/**
 * struct gpio_extcon_platform_data - A simple GPIO-controlled extcon device.
 * @name	The name of this GPIO extcon device.
 * @gpio	Corresponding GPIO.
 * @debounce	Debounce time for GPIO IRQ in ms.
 * @irq_flags	IRQ Flags (e.g., IRQF_TRIGGER_LOW).
 * @state_on	print_state is overriden with state_on if attached. If Null,
 *		default method of extcon class is used.
 * @state_off	print_state is overriden with state_on if detached. If Null,
 *		default method of extcon class is used.
 *
 * Note that in order for state_on or state_off to be valid, both state_on
 * and state_off should be not NULL. If at least one of them is NULL,
 * the print_state is not overriden.
 */
struct gpio_extcon_platform_data {
	const char *name;
	unsigned gpio;
	unsigned long debounce;
	unsigned long irq_flags;

	/* if NULL, "0" or "1" will be printed */
	const char *state_on;
	const char *state_off;
};

#endif /* __EXTCON_GPIO_H__ */
