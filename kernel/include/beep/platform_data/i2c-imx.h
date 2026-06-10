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
#ifndef __ASM_ARCH_I2C_H_
#define __ASM_ARCH_I2C_H_

/**
 * struct imxi2c_platform_data - structure of platform data for MXC I2C driver
 * @bitrate:	Bus speed measured in Hz
 *
 **/
struct imxi2c_platform_data {
	u32 bitrate;
};

#endif /* __ASM_ARCH_I2C_H_ */
