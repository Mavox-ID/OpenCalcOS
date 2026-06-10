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
#ifndef DIB3000MC_H
#define DIB3000MC_H

#include "dibx000_common.h"

struct dib3000mc_config {
	struct dibx000_agc_config *agc;

	u8 phase_noise_mode;
	u8 impulse_noise_mode;

	u8  pwm3_inversion;
	u8  use_pwm3;
	u16 pwm3_value;

	u16 max_time;
	u16 ln_adc_level;

	u8 agc_command1 :1;
	u8 agc_command2 :1;

	u8 mobile_mode;

	u8 output_mpeg2_in_188_bytes;
};

#define DEFAULT_DIB3000MC_I2C_ADDRESS 16
#define DEFAULT_DIB3000P_I2C_ADDRESS  24

#if defined(CONFIG_DVB_DIB3000MC) || (defined(CONFIG_DVB_DIB3000MC_MODULE) && \
				      defined(MODULE))
extern struct dvb_frontend *dib3000mc_attach(struct i2c_adapter *i2c_adap,
					     u8 i2c_addr,
					     struct dib3000mc_config *cfg);
extern int dib3000mc_i2c_enumeration(struct i2c_adapter *i2c,
				     int no_of_demods, u8 default_addr,
				     struct dib3000mc_config cfg[]);
extern
struct i2c_adapter *dib3000mc_get_tuner_i2c_master(struct dvb_frontend *demod,
						   int gating);
#else
static inline
struct dvb_frontend *dib3000mc_attach(struct i2c_adapter *i2c_adap, u8 i2c_addr,
				      struct dib3000mc_config *cfg)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}

static inline
int dib3000mc_i2c_enumeration(struct i2c_adapter *i2c,
			      int no_of_demods, u8 default_addr,
			      struct dib3000mc_config cfg[])
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return -ENODEV;
}

static inline
struct i2c_adapter *dib3000mc_get_tuner_i2c_master(struct dvb_frontend *demod,
						   int gating)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif // CONFIG_DVB_DIB3000MC

extern int dib3000mc_pid_control(struct dvb_frontend *fe, int index, int pid,int onoff);
extern int dib3000mc_pid_parse(struct dvb_frontend *fe, int onoff);

extern void dib3000mc_set_config(struct dvb_frontend *, struct dib3000mc_config *);

#endif
