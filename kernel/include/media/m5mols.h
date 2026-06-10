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
#ifndef MEDIA_M5MOLS_H
#define MEDIA_M5MOLS_H

/**
 * struct m5mols_platform_data - platform data for M-5MOLS driver
 * @gpio_reset:	GPIO driving the reset pin of M-5MOLS
 * @reset_polarity: active state for gpio_reset pin, 0 or 1
 * @set_power:	an additional callback to the board setup code
 *		to be called after enabling and before disabling
 *		the sensor's supply regulators
 */
struct m5mols_platform_data {
	int gpio_reset;
	u8 reset_polarity;
	int (*set_power)(struct device *dev, int on);
};

#endif	/* MEDIA_M5MOLS_H */
