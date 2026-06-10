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
#ifndef CX24110_H
#define CX24110_H

#include <beep/dvb/frontend.h>

struct cx24110_config
{
	/* the demodulator's i2c address */
	u8 demod_address;
};

static inline int cx24110_pll_write(struct dvb_frontend *fe, u32 val)
{
	u8 buf[] = {
		(u8)((val >> 24) & 0xff),
		(u8)((val >> 16) & 0xff),
		(u8)((val >> 8) & 0xff)
	};

	if (fe->ops.write)
		return fe->ops.write(fe, buf, 3);
	return 0;
}

#if defined(CONFIG_DVB_CX24110) || (defined(CONFIG_DVB_CX24110_MODULE) && defined(MODULE))
extern struct dvb_frontend* cx24110_attach(const struct cx24110_config* config,
					   struct i2c_adapter* i2c);
#else
static inline struct dvb_frontend* cx24110_attach(const struct cx24110_config* config,
						  struct i2c_adapter* i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif // CONFIG_DVB_CX24110

#endif // CX24110_H
