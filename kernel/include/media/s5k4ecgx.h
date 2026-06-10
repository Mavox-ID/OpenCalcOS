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
#ifndef S5K4ECGX_H
#define S5K4ECGX_H

/**
 * struct s5k4ecgx_gpio - data structure describing a GPIO
 * @gpio : GPIO number
 * @level: indicates active state of the @gpio
 */
struct s5k4ecgx_gpio {
	int gpio;
	int level;
};

/**
 * struct ss5k4ecgx_platform_data- s5k4ecgx driver platform data
 * @gpio_reset:	 GPIO driving RESET pin
 * @gpio_stby :	 GPIO driving STBY pin
 */

struct s5k4ecgx_platform_data {
	struct s5k4ecgx_gpio gpio_reset;
	struct s5k4ecgx_gpio gpio_stby;
};

#endif /* S5K4ECGX_H */
