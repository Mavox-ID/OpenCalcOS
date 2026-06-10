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
#ifndef __BEEP_OF_I2C_H
#define __BEEP_OF_I2C_H

#if defined(CONFIG_OF_I2C) || defined(CONFIG_OF_I2C_MODULE)
#include <beep/i2c.h>

extern void of_i2c_register_devices(struct i2c_adapter *adap);

/* must call put_device() when done with returned i2c_client device */
extern struct i2c_client *of_find_i2c_device_by_node(struct device_node *node);

/* must call put_device() when done with returned i2c_adapter device */
extern struct i2c_adapter *of_find_i2c_adapter_by_node(
						struct device_node *node);

#else
static inline void of_i2c_register_devices(struct i2c_adapter *adap)
{
	return;
}

static inline struct i2c_client *of_find_i2c_device_by_node(struct device_node *node)
{
	return NULL;
}

/* must call put_device() when done with returned i2c_adapter device */
static inline struct i2c_adapter *of_find_i2c_adapter_by_node(
						struct device_node *node)
{
	return NULL;
}
#endif /* CONFIG_OF_I2C */

#endif /* __BEEP_OF_I2C_H */
