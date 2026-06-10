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
#ifndef RTL2830_PRIV_H
#define RTL2830_PRIV_H

#include "dvb_frontend.h"
#include "dvb_math.h"
#include "rtl2830.h"

struct rtl2830_priv {
	struct i2c_adapter *i2c;
	struct dvb_frontend fe;
	struct rtl2830_config cfg;
	struct i2c_adapter tuner_i2c_adapter;

	bool sleeping;

	u8 page; /* active register page */
};

struct rtl2830_reg_val_mask {
	u16 reg;
	u8  val;
	u8  mask;
};

#endif /* RTL2830_PRIV_H */
