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
#ifndef __MACH_U300_GPIO_U300_H
#define __MACH_U300_GPIO_U300_H

/**
 * struct u300_gpio_platform - U300 GPIO platform data
 * @ports: number of GPIO block ports
 * @gpio_base: first GPIO number for this block (use a free range)
 */
struct u300_gpio_platform {
	u8 ports;
	int gpio_base;
};

#endif /* __MACH_U300_GPIO_U300_H */
