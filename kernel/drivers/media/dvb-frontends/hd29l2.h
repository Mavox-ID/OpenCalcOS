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
#ifndef HD29L2_H
#define HD29L2_H

#include <beep/dvb/frontend.h>

struct hd29l2_config {
	/*
	 * demodulator I2C address
	 */
	u8 i2c_addr;

	/*
	 * tuner I2C address
	 * only needed when tuner is behind demod I2C-gate
	 */
	u8 tuner_i2c_addr;

	/*
	 * TS settings
	 */
#define HD29L2_TS_SERIAL            0x00
#define HD29L2_TS_PARALLEL          0x80
#define HD29L2_TS_CLK_NORMAL        0x40
#define HD29L2_TS_CLK_INVERTED      0x00
#define HD29L2_TS_CLK_GATED         0x20
#define HD29L2_TS_CLK_FREE          0x00
	u8 ts_mode;
};


#if defined(CONFIG_DVB_HD29L2) || \
	(defined(CONFIG_DVB_HD29L2_MODULE) && defined(MODULE))
extern struct dvb_frontend *hd29l2_attach(const struct hd29l2_config *config,
	struct i2c_adapter *i2c);
#else
static inline struct dvb_frontend *hd29l2_attach(
const struct hd29l2_config *config, struct i2c_adapter *i2c)
{
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif

#endif /* HD29L2_H */
