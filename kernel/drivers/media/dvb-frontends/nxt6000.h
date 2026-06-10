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
#ifndef NXT6000_H
#define NXT6000_H

#include <beep/dvb/frontend.h>

struct nxt6000_config
{
	/* the demodulator's i2c address */
	u8 demod_address;

	/* should clock inversion be used? */
	u8 clock_inversion:1;
};

#if defined(CONFIG_DVB_NXT6000) || (defined(CONFIG_DVB_NXT6000_MODULE) && defined(MODULE))
extern struct dvb_frontend* nxt6000_attach(const struct nxt6000_config* config,
					   struct i2c_adapter* i2c);
#else
static inline struct dvb_frontend* nxt6000_attach(const struct nxt6000_config* config,
					   struct i2c_adapter* i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif // CONFIG_DVB_NXT6000

#endif // NXT6000_H
