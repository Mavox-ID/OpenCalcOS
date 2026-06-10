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
#ifndef QT1010_H
#define QT1010_H

#include "dvb_frontend.h"

struct qt1010_config {
	u8 i2c_address;
};

/**
 * Attach a qt1010 tuner to the supplied frontend structure.
 *
 * @param fe   frontend to attach to
 * @param i2c  i2c adapter to use
 * @param cfg  tuner hw based configuration
 * @return fe  pointer on success, NULL on failure
 */
#if defined(CONFIG_MEDIA_TUNER_QT1010) || (defined(CONFIG_MEDIA_TUNER_QT1010_MODULE) && defined(MODULE))
extern struct dvb_frontend *qt1010_attach(struct dvb_frontend *fe,
					  struct i2c_adapter *i2c,
					  struct qt1010_config *cfg);
#else
static inline struct dvb_frontend *qt1010_attach(struct dvb_frontend *fe,
						 struct i2c_adapter *i2c,
						 struct qt1010_config *cfg)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif // CONFIG_MEDIA_TUNER_QT1010

#endif
