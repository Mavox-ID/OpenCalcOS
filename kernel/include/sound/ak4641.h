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
#ifndef __AK4641_H
#define __AK4641_H

/**
 * struct ak4641_platform_data - platform specific AK4641 configuration
 * @gpio_power:	GPIO to control external power to AK4641
 * @gpio_npdn:	GPIO connected to AK4641 nPDN pin
 *
 * Both GPIO parameters are optional.
 */
struct ak4641_platform_data {
	int gpio_power;
	int gpio_npdn;
};

#endif /* __AK4641_H */
