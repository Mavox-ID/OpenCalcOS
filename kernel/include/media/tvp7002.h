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
#ifndef _TVP7002_H_
#define _TVP7002_H_

/* Platform-dependent data
 *
 * clk_polarity:
 * 			0 -> data clocked out on rising edge of DATACLK signal
 * 			1 -> data clocked out on falling edge of DATACLK signal
 * hs_polarity:
 * 			0 -> active low HSYNC output
 * 			1 -> active high HSYNC output
 * sog_polarity:
 * 			0 -> normal operation
 * 			1 -> operation with polarity inverted
 * vs_polarity:
 * 			0 -> active low VSYNC output
 * 			1 -> active high VSYNC output
 * fid_polarity:
 *			0 -> the field ID output is set to logic 1 for an odd
 *			     field (field 1) and set to logic 0 for an even
 *			     field (field 0).
 *			1 -> operation with polarity inverted.
 */
struct tvp7002_config {
	u8 clk_polarity;
	u8 hs_polarity;
	u8 vs_polarity;
	u8 fid_polarity;
	u8 sog_polarity;
};
#endif
