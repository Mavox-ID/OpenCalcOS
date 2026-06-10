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
#ifndef __PLAT_S3C_SPI_CORE_H
#define __PLAT_S3C_SPI_CORE_H

/* These functions are only for use with the core support code, such as
 * the cpu specific initialisation code
 */

/* re-define device name depending on support. */
static inline void s3c64xx_spi_setname(char *name)
{
#ifdef CONFIG_S3C64XX_DEV_SPI0
	s3c64xx_device_spi0.name = name;
#endif
#ifdef CONFIG_S3C64XX_DEV_SPI1
	s3c64xx_device_spi1.name = name;
#endif
#ifdef CONFIG_S3C64XX_DEV_SPI2
	s3c64xx_device_spi2.name = name;
#endif
}

#endif /* __PLAT_S3C_SPI_CORE_H */
