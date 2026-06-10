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
#ifndef TDA8083_H
#define TDA8083_H

#include <beep/dvb/frontend.h>

struct tda8083_config
{
	/* the demodulator's i2c address */
	u8 demod_address;
};

#if defined(CONFIG_DVB_TDA8083) || (defined(CONFIG_DVB_TDA8083_MODULE) && defined(MODULE))
extern struct dvb_frontend* tda8083_attach(const struct tda8083_config* config,
					   struct i2c_adapter* i2c);
#else
static inline struct dvb_frontend* tda8083_attach(const struct tda8083_config* config,
					   struct i2c_adapter* i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif // CONFIG_DVB_TDA8083

#endif // TDA8083_H
