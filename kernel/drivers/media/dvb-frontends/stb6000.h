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
#ifndef __DVB_STB6000_H__
#define __DVB_STB6000_H__

#include <beep/i2c.h>
#include "dvb_frontend.h"

/**
 * Attach a stb6000 tuner to the supplied frontend structure.
 *
 * @param fe Frontend to attach to.
 * @param addr i2c address of the tuner.
 * @param i2c i2c adapter to use.
 * @return FE pointer on success, NULL on failure.
 */
#if defined(CONFIG_DVB_STB6000) || (defined(CONFIG_DVB_STB6000_MODULE) \
							&& defined(MODULE))
extern struct dvb_frontend *stb6000_attach(struct dvb_frontend *fe, int addr,
					   struct i2c_adapter *i2c);
#else
static inline struct dvb_frontend *stb6000_attach(struct dvb_frontend *fe,
						  int addr,
						  struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif /* CONFIG_DVB_STB6000 */

#endif /* __DVB_STB6000_H__ */
