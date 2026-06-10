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
#ifndef __BEEP_V3020_H
#define __BEEP_V3020_H

/* The v3020 has only one data pin but which one
 * is used depends on the board. */
struct v3020_platform_data {
	int leftshift; /* (1<<(leftshift)) & readl() */

	unsigned int use_gpio:1;
	unsigned int gpio_cs;
	unsigned int gpio_wr;
	unsigned int gpio_rd;
	unsigned int gpio_io;
};

#define V3020_STATUS_0	0x00
#define V3020_STATUS_1	0x01
#define V3020_SECONDS	0x02
#define V3020_MINUTES	0x03
#define V3020_HOURS		0x04
#define V3020_MONTH_DAY	0x05
#define V3020_MONTH		0x06
#define V3020_YEAR		0x07
#define V3020_WEEK_DAY	0x08
#define V3020_WEEK		0x09

#define V3020_IS_COMMAND(val) ((val)>=0x0E)

#define V3020_CMD_RAM2CLOCK	0x0E
#define V3020_CMD_CLOCK2RAM	0x0F

#endif /* __BEEP_V3020_H */
