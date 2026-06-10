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
#ifndef __AUO_PIXCIR_TS_H__
#define __AUO_PIXCIR_TS_H__

/*
 * Interrupt modes:
 * periodical:		interrupt is asserted periodicaly
 * compare coordinates:	interrupt is asserted when coordinates change
 * indicate touch:	interrupt is asserted during touch
 */
#define AUO_PIXCIR_INT_PERIODICAL	0x00
#define AUO_PIXCIR_INT_COMP_COORD	0x01
#define AUO_PIXCIR_INT_TOUCH_IND	0x02

/*
 * @gpio_int		interrupt gpio
 * @int_setting		one of AUO_PIXCIR_INT_*
 * @init_hw		hardwarespecific init
 * @exit_hw		hardwarespecific shutdown
 * @x_max		x-resolution
 * @y_max		y-resolution
 */
struct auo_pixcir_ts_platdata {
	int gpio_int;

	int int_setting;

	void (*init_hw)(struct i2c_client *);
	void (*exit_hw)(struct i2c_client *);

	unsigned int x_max;
	unsigned int y_max;
};

#endif
