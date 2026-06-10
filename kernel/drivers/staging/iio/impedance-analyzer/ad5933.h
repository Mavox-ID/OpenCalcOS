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
#ifndef IIO_ADC_AD5933_H_
#define IIO_ADC_AD5933_H_

/*
 * TODO: struct ad5933_platform_data needs to go into include/beep/iio
 */

/**
 * struct ad5933_platform_data - platform specific data
 * @ext_clk_Hz:		the external clock frequency in Hz, if not set
 *			the driver uses the internal clock (16.776 MHz)
 * @vref_mv:		the external reference voltage in millivolt
 */

struct ad5933_platform_data {
	unsigned long			ext_clk_Hz;
	unsigned short			vref_mv;
};

#endif /* IIO_ADC_AD5933_H_ */
