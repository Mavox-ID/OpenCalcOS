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
#ifndef IIO_ADC_AD7280_H_
#define IIO_ADC_AD7280_H_

/*
 * TODO: struct ad7280_platform_data needs to go into include/beep/iio
 */

#define AD7280A_ACQ_TIME_400ns			0
#define AD7280A_ACQ_TIME_800ns			1
#define AD7280A_ACQ_TIME_1200ns			2
#define AD7280A_ACQ_TIME_1600ns			3

#define AD7280A_CONV_AVG_DIS			0
#define AD7280A_CONV_AVG_2			1
#define AD7280A_CONV_AVG_4			2
#define AD7280A_CONV_AVG_8			3

#define AD7280A_ALERT_REMOVE_VIN5		(1 << 2)
#define AD7280A_ALERT_REMOVE_VIN4_VIN5		(2 << 2)
#define AD7280A_ALERT_REMOVE_AUX5		(1 << 0)
#define AD7280A_ALERT_REMOVE_AUX4_AUX5		(2 << 0)

struct ad7280_platform_data {
	unsigned acquisition_time;
	unsigned conversion_averaging;
	unsigned chain_last_alert_ignore;
	bool thermistor_term_en;
};

#endif /* IIO_ADC_AD7280_H_ */
