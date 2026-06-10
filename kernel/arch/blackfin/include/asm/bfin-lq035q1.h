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
#ifndef BFIN_LQ035Q1_H
#define BFIN_LQ035Q1_H

/*
 * LCD Modes
 */
#define LQ035_RL	(0 << 8)	/* Right -> Left Scan */
#define LQ035_LR	(1 << 8)	/* Left -> Right Scan */
#define LQ035_TB	(1 << 9)	/* Top -> Botton Scan */
#define LQ035_BT	(0 << 9)	/* Botton -> Top Scan */
#define LQ035_BGR	(1 << 11)	/* Use BGR format */
#define LQ035_RGB	(0 << 11)	/* Use RGB format */
#define LQ035_NORM	(1 << 13)	/* Reversal */
#define LQ035_REV	(0 << 13)	/* Reversal */

/*
 * PPI Modes
 */

#define USE_RGB565_16_BIT_PPI	1
#define USE_RGB565_8_BIT_PPI	2
#define USE_RGB888_8_BIT_PPI	3

struct bfin_lq035q1fb_disp_info {

	unsigned	mode;
	unsigned	ppi_mode;
	/* GPIOs */
	int		use_bl;
	unsigned 	gpio_bl;
};

#endif /* BFIN_LQ035Q1_H */
