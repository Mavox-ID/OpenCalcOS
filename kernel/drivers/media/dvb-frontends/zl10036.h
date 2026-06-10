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
#ifndef DVB_ZL10036_H
#define DVB_ZL10036_H

#include <beep/i2c.h>
#include "dvb_frontend.h"

/**
 * Attach a zl10036 tuner to the supplied frontend structure.
 *
 * @param fe Frontend to attach to.
 * @param config zl10036_config structure
 * @return FE pointer on success, NULL on failure.
 */

struct zl10036_config {
	u8 tuner_address;
	int rf_loop_enable;
};

#if defined(CONFIG_DVB_ZL10036) || \
	(defined(CONFIG_DVB_ZL10036_MODULE) && defined(MODULE))
extern struct dvb_frontend *zl10036_attach(struct dvb_frontend *fe,
	const struct zl10036_config *config, struct i2c_adapter *i2c);
#else
static inline struct dvb_frontend *zl10036_attach(struct dvb_frontend *fe,
	const struct zl10036_config *config, struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif

#endif /* DVB_ZL10036_H */
