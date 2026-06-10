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
#ifndef TUA9001_H
#define TUA9001_H

#include "dvb_frontend.h"

struct tua9001_config {
	/*
	 * I2C address
	 */
	u8 i2c_addr;
};

/*
 * TUA9001 I/O PINs:
 *
 * CEN - chip enable
 * 0 = chip disabled (chip off)
 * 1 = chip enabled (chip on)
 *
 * RESETN - chip reset
 * 0 = reset disabled (chip reset off)
 * 1 = reset enabled (chip reset on)
 *
 * RXEN - RX enable
 * 0 = RX disabled (chip idle)
 * 1 = RX enabled (chip tuned)
 */

#define TUA9001_CMD_CEN     0
#define TUA9001_CMD_RESETN  1
#define TUA9001_CMD_RXEN    2

#if defined(CONFIG_MEDIA_TUNER_TUA9001) || \
	(defined(CONFIG_MEDIA_TUNER_TUA9001_MODULE) && defined(MODULE))
extern struct dvb_frontend *tua9001_attach(struct dvb_frontend *fe,
		struct i2c_adapter *i2c, struct tua9001_config *cfg);
#else
static inline struct dvb_frontend *tua9001_attach(struct dvb_frontend *fe,
		struct i2c_adapter *i2c, struct tua9001_config *cfg)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif

#endif
