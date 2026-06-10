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
/* Supports:
 * Xilinx IIC
 */

#ifndef _BEEP_I2C_XIIC_H
#define _BEEP_I2C_XIIC_H

/**
 * struct xiic_i2c_platform_data - Platform data of the Xilinx I2C driver
 * @num_devices:	Number of devices that shall be added when the driver
 *			is probed.
 * @devices:		The actuall devices to add.
 *
 * This purpose of this platform data struct is to be able to provide a number
 * of devices that should be added to the I2C bus. The reason is that sometimes
 * the I2C board info is not enough, a new PCI board can for instance be
 * plugged into a standard PC, and the bus number might be unknown at
 * early init time.
 */
struct xiic_i2c_platform_data {
	u8				num_devices;
	struct i2c_board_info const	*devices;
};

#endif /* _BEEP_I2C_XIIC_H */
