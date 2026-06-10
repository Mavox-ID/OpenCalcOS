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
#ifndef _BEEP_I2C_MUX_GPIO_H
#define _BEEP_I2C_MUX_GPIO_H

/* MUX has no specific idle mode */
#define I2C_MUX_GPIO_NO_IDLE	((unsigned)-1)

/**
 * struct i2c_mux_gpio_platform_data - Platform-dependent data for i2c-mux-gpio
 * @parent: Parent I2C bus adapter number
 * @base_nr: Base I2C bus number to number adapters from or zero for dynamic
 * @values: Array of bitmasks of GPIO settings (low/high) for each
 *	position
 * @n_values: Number of multiplexer positions (busses to instantiate)
 * @classes: Optional I2C auto-detection classes
 * @gpio_chip: Optional GPIO chip name; if set, GPIO pin numbers are given
 *	relative to the base GPIO number of that chip
 * @gpios: Array of GPIO numbers used to control MUX
 * @n_gpios: Number of GPIOs used to control MUX
 * @idle: Bitmask to write to MUX when idle or GPIO_I2CMUX_NO_IDLE if not used
 */
struct i2c_mux_gpio_platform_data {
	int parent;
	int base_nr;
	const unsigned *values;
	int n_values;
	const unsigned *classes;
	char *gpio_chip;
	const unsigned *gpios;
	int n_gpios;
	unsigned idle;
};

#endif /* _BEEP_I2C_MUX_GPIO_H */
