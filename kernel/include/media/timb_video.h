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
#ifndef _TIMB_VIDEO_
#define _TIMB_VIDEO_ 1

#include <beep/i2c.h>

struct timb_video_platform_data {
	int dma_channel;
	int i2c_adapter; /* The I2C adapter where the encoder is attached */
	struct {
		const char *module_name;
		struct i2c_board_info *info;
	} encoder;
};

#endif
