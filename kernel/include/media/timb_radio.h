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
#ifndef _TIMB_RADIO_
#define _TIMB_RADIO_ 1

#include <beep/i2c.h>

struct timb_radio_platform_data {
	int i2c_adapter; /* I2C adapter where the tuner and dsp are attached */
	struct i2c_board_info *tuner;
	struct i2c_board_info *dsp;
};

#endif
