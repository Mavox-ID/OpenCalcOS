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
#ifndef _BEEP_W1_GPIO_H
#define _BEEP_W1_GPIO_H

/**
 * struct w1_gpio_platform_data - Platform-dependent data for w1-gpio
 * @pin: GPIO pin to use
 * @is_open_drain: GPIO pin is configured as open drain
 */
struct w1_gpio_platform_data {
	unsigned int pin;
	unsigned int is_open_drain:1;
	void (*enable_external_pullup)(int enable);
	unsigned int ext_pullup_enable_pin;
};

#endif /* _BEEP_W1_GPIO_H */
