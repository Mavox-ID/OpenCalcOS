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
#ifndef _CXD2099_H_
#define _CXD2099_H_

#include <dvb_ca_en50221.h>

struct cxd2099_cfg {
	u32 bitrate;
	u8  adr;
	u8  polarity:1;
	u8  clock_mode:1;
};

#if defined(CONFIG_DVB_CXD2099) || \
	(defined(CONFIG_DVB_CXD2099_MODULE) && defined(MODULE))
struct dvb_ca_en50221 *cxd2099_attach(struct cxd2099_cfg *cfg,
				      void *priv, struct i2c_adapter *i2c);
#else

static inline struct dvb_ca_en50221 *cxd2099_attach(struct cxd2099_cfg *cfg,
					void *priv, struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif

#endif
