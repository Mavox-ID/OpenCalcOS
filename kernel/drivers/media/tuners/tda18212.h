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
#ifndef TDA18212_H
#define TDA18212_H

#include "dvb_frontend.h"

struct tda18212_config {
	u8 i2c_address;

	u16 if_dvbt_6;
	u16 if_dvbt_7;
	u16 if_dvbt_8;
	u16 if_dvbt2_5;
	u16 if_dvbt2_6;
	u16 if_dvbt2_7;
	u16 if_dvbt2_8;
	u16 if_dvbc;
};

#if defined(CONFIG_MEDIA_TUNER_TDA18212) || \
	(defined(CONFIG_MEDIA_TUNER_TDA18212_MODULE) && defined(MODULE))
extern struct dvb_frontend *tda18212_attach(struct dvb_frontend *fe,
	struct i2c_adapter *i2c, struct tda18212_config *cfg);
#else
static inline struct dvb_frontend *tda18212_attach(struct dvb_frontend *fe,
	struct i2c_adapter *i2c, struct tda18212_config *cfg)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif

#endif
