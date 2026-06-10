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
#ifndef IIO_ADC_AD7887_H_
#define IIO_ADC_AD7887_H_

/**
 * struct ad7887_platform_data - AD7887 ADC driver platform data
 * @en_dual: Whether to use dual channel mode. If set to true AIN1 becomes the
 *	second input channel, and Vref is internally connected to Vdd. If set to
 *	false the device is used in single channel mode and AIN1/Vref is used as
 *	VREF input.
 * @use_onchip_ref: Whether to use the onchip reference. If set to true the
 *	internal 2.5V reference is used. If set to false a external reference is
 *	used.
 */
struct ad7887_platform_data {
	bool en_dual;
	bool use_onchip_ref;
};

#endif /* IIO_ADC_AD7887_H_ */
