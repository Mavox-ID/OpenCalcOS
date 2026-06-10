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
/**
 * struct sht15_platform_data - sht15 connectivity info
 * @gpio_data:		no. of gpio to which bidirectional data line is
 *			connected.
 * @gpio_sck:		no. of gpio to which the data clock is connected.
 * @supply_mv:		supply voltage in mv. Overridden by regulator if
 *			available.
 * @checksum:		flag to indicate the checksum should be validated.
 * @no_otp_reload:	flag to indicate no reload from OTP.
 * @low_resolution:	flag to indicate the tmp/humidity resolution to use.
 */
struct sht15_platform_data {
	int gpio_data;
	int gpio_sck;
	int supply_mv;
	bool checksum;
	bool no_otp_reload;
	bool low_resolution;
};
