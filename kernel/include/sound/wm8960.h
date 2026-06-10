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
#ifndef _WM8960_PDATA_H
#define _WM8960_PDATA_H

#define WM8960_DRES_400R 0
#define WM8960_DRES_200R 1
#define WM8960_DRES_600R 2
#define WM8960_DRES_150R 3
#define WM8960_DRES_MAX  3

struct wm8960_data {
	bool capless;  /* Headphone outputs configured in capless mode */

	bool shared_lrclk;  /* DAC and ADC LRCLKs are wired together */
};

#endif
