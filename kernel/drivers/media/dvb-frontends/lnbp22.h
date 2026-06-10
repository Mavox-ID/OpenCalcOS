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
#ifndef _LNBP22_H
#define _LNBP22_H

/* Enable */
#define LNBP22_EN	  0x10
/* Voltage selection */
#define LNBP22_VSEL	0x02
/* Plus 1 Volt Bit */
#define LNBP22_LLC	0x01

#include <beep/dvb/frontend.h>

#if defined(CONFIG_DVB_LNBP22) || \
		(defined(CONFIG_DVB_LNBP22_MODULE) && defined(MODULE))
/*
 * override_set and override_clear control which system register bits (above)
 * to always set & clear
 */
extern struct dvb_frontend *lnbp22_attach(struct dvb_frontend *fe,
						struct i2c_adapter *i2c);
#else
static inline struct dvb_frontend *lnbp22_attach(struct dvb_frontend *fe,
						struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif /* CONFIG_DVB_LNBP22 */

#endif /* _LNBP22_H */
