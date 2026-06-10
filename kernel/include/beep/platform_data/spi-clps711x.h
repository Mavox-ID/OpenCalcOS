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
#ifndef ____BEEP_PLATFORM_DATA_SPI_CLPS711X_H
#define ____BEEP_PLATFORM_DATA_SPI_CLPS711X_H

/* Board specific platform_data */
struct spi_clps711x_pdata {
	int *chipselect;	/* Array of GPIO-numbers */
	int num_chipselect;	/* Total count of GPIOs */
};

#endif
