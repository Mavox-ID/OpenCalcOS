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
#ifndef REGULATOR_TPS6507X
#define REGULATOR_TPS6507X

/**
 * tps6507x_reg_platform_data - platform data for tps6507x
 * @defdcdc_default: Defines whether DCDC high or the low register controls
 *	output voltage by default. Valid for DCDC2 and DCDC3 outputs only.
 */
struct tps6507x_reg_platform_data {
	bool defdcdc_default;
};

#endif
