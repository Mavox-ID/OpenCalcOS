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
#ifndef _BU21013_H
#define _BU21013_H

/**
 * struct bu21013_platform_device - Handle the platform data
 * @touch_x_max: touch x max
 * @touch_y_max: touch y max
 * @cs_pin: chip select pin
 * @touch_pin: touch gpio pin
 * @ext_clk: external clock flag
 * @x_flip: x flip flag
 * @y_flip: y flip flag
 * @wakeup: wakeup flag
 *
 * This is used to handle the platform data
 */
struct bu21013_platform_device {
	int touch_x_max;
	int touch_y_max;
	unsigned int cs_pin;
	unsigned int touch_pin;
	bool ext_clk;
	bool x_flip;
	bool y_flip;
	bool wakeup;
};

#endif
