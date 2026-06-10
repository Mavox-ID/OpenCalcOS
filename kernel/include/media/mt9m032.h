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
#ifndef MT9M032_H
#define MT9M032_H

#define MT9M032_NAME		"mt9m032"
#define MT9M032_I2C_ADDR	(0xb8 >> 1)

struct mt9m032_platform_data {
	u32 ext_clock;
	u32 pix_clock;
	bool invert_pixclock;

};
#endif /* MT9M032_H */
