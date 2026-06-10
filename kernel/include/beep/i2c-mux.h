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
#ifndef _BEEP_I2C_MUX_H
#define _BEEP_I2C_MUX_H

#ifdef __KERNEL__

/*
 * Called to create a i2c bus on a multiplexed bus segment.
 * The mux_dev and chan_id parameters are passed to the select
 * and deselect callback functions to perform hardware-specific
 * mux control.
 */
struct i2c_adapter *i2c_add_mux_adapter(struct i2c_adapter *parent,
				struct device *mux_dev,
				void *mux_priv, u32 force_nr, u32 chan_id,
				unsigned int class,
				int (*select) (struct i2c_adapter *,
					       void *mux_dev, u32 chan_id),
				int (*deselect) (struct i2c_adapter *,
						 void *mux_dev, u32 chan_id));

int i2c_del_mux_adapter(struct i2c_adapter *adap);

#endif /* __KERNEL__ */

#endif /* _BEEP_I2C_MUX_H */
