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
#ifndef MB86A20S_H
#define MB86A20S_H

#include <beep/dvb/frontend.h>

/**
 * struct mb86a20s_config - Define the per-device attributes of the frontend
 *
 * @demod_address:	the demodulator's i2c address
 */

struct mb86a20s_config {
	u8 demod_address;
	bool is_serial;
};

#if defined(CONFIG_DVB_MB86A20S) || (defined(CONFIG_DVB_MB86A20S_MODULE) \
	&& defined(MODULE))
extern struct dvb_frontend *mb86a20s_attach(const struct mb86a20s_config *config,
					   struct i2c_adapter *i2c);
extern struct i2c_adapter *mb86a20s_get_tuner_i2c_adapter(struct dvb_frontend *);
#else
static inline struct dvb_frontend *mb86a20s_attach(
	const struct mb86a20s_config *config, struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
static struct i2c_adapter *
	mb86a20s_get_tuner_i2c_adapter(struct dvb_frontend *fe)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif

#endif /* MB86A20S */
