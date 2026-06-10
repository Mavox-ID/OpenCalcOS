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
#ifndef ZL10039_H
#define ZL10039_H

#if defined(CONFIG_DVB_ZL10039) || (defined(CONFIG_DVB_ZL10039_MODULE) \
	    && defined(MODULE))
struct dvb_frontend *zl10039_attach(struct dvb_frontend *fe,
					u8 i2c_addr,
					struct i2c_adapter *i2c);
#else
static inline struct dvb_frontend *zl10039_attach(struct dvb_frontend *fe,
					u8 i2c_addr,
					struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif /* CONFIG_DVB_ZL10039 */

#endif /* ZL10039_H */
