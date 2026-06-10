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
#ifndef _AU1550_SPI_H_
#define _AU1550_SPI_H_

struct au1550_spi_info {
	u32 mainclk_hz;		/* main input clock frequency of PSC */
	u16 num_chipselect;	/* number of chipselects supported */
	void (*activate_cs)(struct au1550_spi_info *spi, int cs, int polarity);
	void (*deactivate_cs)(struct au1550_spi_info *spi, int cs, int polarity);
};

#endif
