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
#ifndef MT352_H
#define MT352_H

#include <beep/dvb/frontend.h>

struct mt352_config
{
	/* the demodulator's i2c address */
	u8 demod_address;

	/* frequencies in kHz */
	int adc_clock;  // default: 20480
	int if2;        // default: 36166

	/* set if no pll is connected to the secondary i2c bus */
	int no_tuner;

	/* Initialise the demodulator and PLL. Cannot be NULL */
	int (*demod_init)(struct dvb_frontend* fe);
};

#if defined(CONFIG_DVB_MT352) || (defined(CONFIG_DVB_MT352_MODULE) && defined(MODULE))
extern struct dvb_frontend* mt352_attach(const struct mt352_config* config,
					 struct i2c_adapter* i2c);
#else
static inline struct dvb_frontend* mt352_attach(const struct mt352_config* config,
					 struct i2c_adapter* i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif // CONFIG_DVB_MT352

static inline int mt352_write(struct dvb_frontend *fe, const u8 buf[], int len) {
	int r = 0;
	if (fe->ops.write)
		r = fe->ops.write(fe, buf, len);
	return r;
}

#endif // MT352_H
