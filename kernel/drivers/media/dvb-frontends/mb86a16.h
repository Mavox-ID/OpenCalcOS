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
#ifndef __MB86A16_H
#define __MB86A16_H

#include <beep/dvb/frontend.h>
#include "dvb_frontend.h"


struct mb86a16_config {
	u8 demod_address;

	int (*set_voltage)(struct dvb_frontend *fe, fe_sec_voltage_t voltage);
};



#if defined(CONFIG_DVB_MB86A16) || (defined(CONFIG_DVB_MB86A16_MODULE) && defined(MODULE))

extern struct dvb_frontend *mb86a16_attach(const struct mb86a16_config *config,
					   struct i2c_adapter *i2c_adap);

#else

static inline struct dvb_frontend *mb86a16_attach(const struct mb86a16_config *config,
					   struct i2c_adapter *i2c_adap)
{
	printk(KERN_WARNING "%s: Driver disabled by Kconfig\n", __func__);
	return NULL;
}

#endif /* CONFIG_DVB_MB86A16 */

#endif /* __MB86A16_H */
