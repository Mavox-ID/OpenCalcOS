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
#ifndef NXT200X_H
#define NXT200X_H

#include <beep/dvb/frontend.h>
#include <beep/firmware.h>

typedef enum nxt_chip_t {
		NXTUNDEFINED,
		NXT2002,
		NXT2004
}nxt_chip_type;

struct nxt200x_config
{
	/* the demodulator's i2c address */
	u8 demod_address;

	/* need to set device param for start_dma */
	int (*set_ts_params)(struct dvb_frontend* fe, int is_punctured);
};

#if defined(CONFIG_DVB_NXT200X) || (defined(CONFIG_DVB_NXT200X_MODULE) && defined(MODULE))
extern struct dvb_frontend* nxt200x_attach(const struct nxt200x_config* config,
					   struct i2c_adapter* i2c);
#else
static inline struct dvb_frontend* nxt200x_attach(const struct nxt200x_config* config,
					   struct i2c_adapter* i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif // CONFIG_DVB_NXT200X

#endif /* NXT200X_H */

/*
 * Local variables:
 * c-basic-offset: 8
 * End:
 */
