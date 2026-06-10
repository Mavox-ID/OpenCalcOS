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
#ifndef _LIBERTAS_SPI_H_
#define _LIBERTAS_SPI_H_

struct spi_device;

struct libertas_spi_platform_data {
	/* There are two ways to read data from the WLAN module's SPI
	 * interface. Setting 0 or 1 here controls which one is used.
	 *
	 * Usually you want to set use_dummy_writes = 1.
	 * However, if that doesn't work or if you are using a slow SPI clock
	 * speed, you may want to use 0 here. */
	u16 use_dummy_writes;

	/* Board specific setup/teardown */
	int (*setup)(struct spi_device *spi);
	int (*teardown)(struct spi_device *spi);
};
#endif
