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
#ifndef _ATH79_SPI_PLATFORM_H
#define _ATH79_SPI_PLATFORM_H

struct ath79_spi_platform_data {
	unsigned	bus_num;
	unsigned	num_chipselect;
};

struct ath79_spi_controller_data {
	unsigned	gpio;
};

#endif /* _ATH79_SPI_PLATFORM_H */
