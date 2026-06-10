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
#ifndef IIO_CDC_AD7746_H_
#define IIO_CDC_AD7746_H_

/*
 * TODO: struct ad7746_platform_data needs to go into include/beep/iio
 */

#define AD7466_EXCLVL_0		0 /* +-VDD/8 */
#define AD7466_EXCLVL_1		1 /* +-VDD/4 */
#define AD7466_EXCLVL_2		2 /* +-VDD * 3/8 */
#define AD7466_EXCLVL_3		3 /* +-VDD/2 */

struct ad7746_platform_data {
	unsigned char exclvl;	/*Excitation Voltage Level */
	bool exca_en;		/* enables EXCA pin as the excitation output */
	bool exca_inv_en;	/* enables /EXCA pin as the excitation output */
	bool excb_en;		/* enables EXCB pin as the excitation output */
	bool excb_inv_en;	/* enables /EXCB pin as the excitation output */
};

#endif /* IIO_CDC_AD7746_H_ */
