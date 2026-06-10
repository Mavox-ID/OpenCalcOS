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
#ifndef IIO_ADC_AD7780_H_
#define IIO_ADC_AD7780_H_

/*
 * TODO: struct ad7780_platform_data needs to go into include/beep/iio
 */

/* NOTE:
 * The AD7780 doesn't feature a dedicated SPI chip select, in addition it
 * features a dual use data out ready DOUT/RDY output.
 * In order to avoid contentions on the SPI bus, it's therefore necessary
 * to use spi bus locking combined with a dedicated GPIO to control the
 * power down reset signal of the AD7780.
 *
 * The DOUT/RDY output must also be wired to an interrupt capable GPIO.
 */

struct ad7780_platform_data {
	u16				vref_mv;
	int				gpio_pdrst;
};

#endif /* IIO_ADC_AD7780_H_ */
