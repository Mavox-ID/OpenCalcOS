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
#ifndef __I2C_DESIGNWARE_H
#define __I2C_DESIGNWARE_H

/**
 * struct i2c_dw_platdata - Platform device data for DesignWare I2C adapter
 * Speed dividers will be calculated based on the given speed if they're 0.
 * @ss_hcnt: Standard-mode speed divider for high period
 * @ss_lcnt: Standard-mode speed divider for low period
 * @fs_hcnt: Fast speed divider for high period
 * @fs_lcnt: Fast speed divider for low period
 */
struct i2c_dw_platdata {
	u32 ss_hcnt;
	u32 ss_lcnt;
	u32 fs_hcnt;
	u32 fs_lcnt;
};

#endif /* __I2C_DESIGNWARE_H */
