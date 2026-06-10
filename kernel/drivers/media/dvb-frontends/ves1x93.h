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
#ifndef VES1X93_H
#define VES1X93_H

#include <beep/dvb/frontend.h>

struct ves1x93_config
{
	/* the demodulator's i2c address */
	u8 demod_address;

	/* value of XIN to use */
	u32 xin;

	/* should PWM be inverted? */
	u8 invert_pwm:1;
};

#if defined(CONFIG_DVB_VES1X93) || (defined(CONFIG_DVB_VES1X93_MODULE) && defined(MODULE))
extern struct dvb_frontend* ves1x93_attach(const struct ves1x93_config* config,
					   struct i2c_adapter* i2c);
#else
static inline struct dvb_frontend* ves1x93_attach(const struct ves1x93_config* config,
					   struct i2c_adapter* i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif // CONFIG_DVB_VES1X93

#endif // VES1X93_H
