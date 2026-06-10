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
#ifndef __ASM_ARCH_IIC_CORE_H
#define __ASM_ARCH_IIC_CORE_H __FILE__

/* These functions are only for use with the core support code, such as
 * the cpu specific initialisation code
 */

/* re-define device name depending on support. */
static inline void s3c_i2c0_setname(char *name)
{
	/* currently this device is always compiled in */
	s3c_device_i2c0.name = name;
}

static inline void s3c_i2c1_setname(char *name)
{
#ifdef CONFIG_S3C_DEV_I2C1
	s3c_device_i2c1.name = name;
#endif
}

static inline void s3c_i2c2_setname(char *name)
{
#ifdef CONFIG_S3C_DEV_I2C2
	s3c_device_i2c2.name = name;
#endif
}

#endif /* __ASM_ARCH_IIC_H */
