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
#ifndef STV0367_H
#define STV0367_H

#include <beep/dvb/frontend.h>
#include "dvb_frontend.h"

struct stv0367_config {
	u8 demod_address;
	u32 xtal;
	u32 if_khz;/*4500*/
	int if_iq_mode;
	int ts_mode;
	int clk_pol;
};

#if defined(CONFIG_DVB_STV0367) || (defined(CONFIG_DVB_STV0367_MODULE) \
							&& defined(MODULE))
extern struct
dvb_frontend *stv0367ter_attach(const struct stv0367_config *config,
					struct i2c_adapter *i2c);
extern struct
dvb_frontend *stv0367cab_attach(const struct stv0367_config *config,
					struct i2c_adapter *i2c);
#else
static inline struct
dvb_frontend *stv0367ter_attach(const struct stv0367_config *config,
					struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
static inline struct
dvb_frontend *stv0367cab_attach(const struct stv0367_config *config,
					struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif

#endif
