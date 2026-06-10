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
#ifndef SH_VOU_H
#define SH_VOU_H

#include <beep/i2c.h>

/* Bus flags */
#define SH_VOU_PCLK_FALLING	(1 << 0)
#define SH_VOU_HSYNC_LOW	(1 << 1)
#define SH_VOU_VSYNC_LOW	(1 << 2)

enum sh_vou_bus_fmt {
	SH_VOU_BUS_8BIT,
	SH_VOU_BUS_16BIT,
	SH_VOU_BUS_BT656,
};

struct sh_vou_pdata {
	enum sh_vou_bus_fmt bus_fmt;
	int i2c_adap;
	struct i2c_board_info *board_info;
	unsigned long flags;
};

#endif
