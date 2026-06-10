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
#ifndef __TDA9887_H__
#define __TDA9887_H__

#include <beep/i2c.h>
#include "dvb_frontend.h"

/* ------------------------------------------------------------------------ */
#if defined(CONFIG_MEDIA_TUNER_TDA9887) || (defined(CONFIG_MEDIA_TUNER_TDA9887_MODULE) && defined(MODULE))
extern struct dvb_frontend *tda9887_attach(struct dvb_frontend *fe,
					   struct i2c_adapter *i2c_adap,
					   u8 i2c_addr);
#else
static inline struct dvb_frontend *tda9887_attach(struct dvb_frontend *fe,
						  struct i2c_adapter *i2c_adap,
						  u8 i2c_addr)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif

#endif /* __TDA9887_H__ */
