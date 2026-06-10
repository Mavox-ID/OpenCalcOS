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
#ifndef _PDATA_ADS7828_H
#define _PDATA_ADS7828_H

/**
 * struct ads7828_platform_data - optional ADS7828 connectivity info
 * @diff_input:		Differential input mode.
 * @ext_vref:		Use an external voltage reference.
 * @vref_mv:		Voltage reference value, if external.
 */
struct ads7828_platform_data {
	bool diff_input;
	bool ext_vref;
	unsigned int vref_mv;
};

#endif /* _PDATA_ADS7828_H */
