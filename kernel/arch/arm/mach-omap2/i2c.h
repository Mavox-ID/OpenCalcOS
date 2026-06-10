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
#include <plat/i2c.h>

#ifndef __MACH_OMAP2_I2C_H
#define __MACH_OMAP2_I2C_H

/**
 * i2c_dev_attr - OMAP I2C controller device attributes for omap_hwmod
 * @fifo_depth: total controller FIFO size (in bytes)
 * @flags: differences in hardware support capability
 *
 * @fifo_depth represents what exists on the hardware, not what is
 * actually configured at runtime by the device driver.
 */
struct omap_i2c_dev_attr {
	u8	fifo_depth;
	u32	flags;
};

int omap_i2c_reset(struct omap_hwmod *oh);

#endif	/* __MACH_OMAP2_I2C_H */
