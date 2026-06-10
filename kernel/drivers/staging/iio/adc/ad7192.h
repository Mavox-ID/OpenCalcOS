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
#ifndef IIO_ADC_AD7192_H_
#define IIO_ADC_AD7192_H_

/*
 * TODO: struct ad7192_platform_data needs to go into include/beep/iio
 */

/**
 * struct ad7192_platform_data - platform/board specific information
 * @vref_mv:		the external reference voltage in millivolt
 * @clock_source_sel:	[0..3]
 *			0 External 4.92 MHz clock connected from MCLK1 to MCLK2
 *			1 External Clock applied to MCLK2
 *			2 Internal 4.92 MHz Clock not available at the MCLK2 pin
 *			3 Internal 4.92 MHz Clock available at the MCLK2 pin
 * @ext_clk_Hz:		the external clock frequency in Hz, if not set
 *			the driver uses the internal clock (16.776 MHz)
 * @refin2_en:		REFIN1/REFIN2 Reference Select (AD7190/2 only)
 * @rej60_en:		50/60Hz notch filter enable
 * @sinc3_en:		SINC3 filter enable (default SINC4)
 * @chop_en:		CHOP mode enable
 * @buf_en:		buffered input mode enable
 * @unipolar_en:	unipolar mode enable
 * @burnout_curr_en:	constant current generators on AIN(+|-) enable
 */

struct ad7192_platform_data {
	u16		vref_mv;
	u8		clock_source_sel;
	u32		ext_clk_Hz;
	bool		refin2_en;
	bool		rej60_en;
	bool		sinc3_en;
	bool		chop_en;
	bool		buf_en;
	bool		unipolar_en;
	bool		burnout_curr_en;
};

#endif /* IIO_ADC_AD7192_H_ */
