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
#ifndef __BEEP_I2C_TPS6507X_TS_H
#define __BEEP_I2C_TPS6507X_TS_H

/* Board specific touch screen initial values */
struct touchscreen_init_data {
	int	poll_period;	/* ms */
	int	vref;		/* non-zero to leave vref on */
	__u16	min_pressure;	/* min reading to be treated as a touch */
	__u16	vendor;
	__u16	product;
	__u16	version;
};

#endif /*  __BEEP_I2C_TPS6507X_TS_H */
