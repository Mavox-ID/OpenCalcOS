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
#ifndef CX24113_H
#define CX24113_H

struct dvb_frontend;

struct cx24113_config {
	u8 i2c_addr; /* 0x14 or 0x54 */

	u32 xtal_khz;
};

#if defined(CONFIG_DVB_TUNER_CX24113) || \
	(defined(CONFIG_DVB_TUNER_CX24113_MODULE) && defined(MODULE))
extern struct dvb_frontend *cx24113_attach(struct dvb_frontend *,
	const struct cx24113_config *config, struct i2c_adapter *i2c);

extern void cx24113_agc_callback(struct dvb_frontend *fe);
#else
static inline struct dvb_frontend *cx24113_attach(struct dvb_frontend *fe,
	const struct cx24113_config *config, struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}

static inline void cx24113_agc_callback(struct dvb_frontend *fe)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
}
#endif

#endif /* CX24113_H */
