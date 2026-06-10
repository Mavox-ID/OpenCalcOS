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
#ifndef FC2580_H
#define FC2580_H

#include "dvb_frontend.h"

struct fc2580_config {
	/*
	 * I2C address
	 * 0x56, ...
	 */
	u8 i2c_addr;

	/*
	 * clock
	 */
	u32 clock;
};

#if defined(CONFIG_MEDIA_TUNER_FC2580) || \
	(defined(CONFIG_MEDIA_TUNER_FC2580_MODULE) && defined(MODULE))
extern struct dvb_frontend *fc2580_attach(struct dvb_frontend *fe,
	struct i2c_adapter *i2c, const struct fc2580_config *cfg);
#else
static inline struct dvb_frontend *fc2580_attach(struct dvb_frontend *fe,
	struct i2c_adapter *i2c, const struct fc2580_config *cfg)
{
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif

#endif
