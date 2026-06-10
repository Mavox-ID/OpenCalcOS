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
#ifndef _CYTTSP_H_
#define _CYTTSP_H_

#define CY_SPI_NAME "cyttsp-spi"
#define CY_I2C_NAME "cyttsp-i2c"
/* Active Power state scanning/processing refresh interval */
#define CY_ACT_INTRVL_DFLT 0x00 /* ms */
/* touch timeout for the Active power */
#define CY_TCH_TMOUT_DFLT 0xFF /* ms */
/* Low Power state scanning/processing refresh interval */
#define CY_LP_INTRVL_DFLT 0x0A /* ms */
/* Active distance in pixels for a gesture to be reported */
#define CY_ACT_DIST_DFLT 0xF8 /* pixels */

struct cyttsp_platform_data {
	u32 maxx;
	u32 maxy;
	bool use_hndshk;
	u8 act_dist;	/* Active distance */
	u8 act_intrvl;  /* Active refresh interval; ms */
	u8 tch_tmout;   /* Active touch timeout; ms */
	u8 lp_intrvl;   /* Low power refresh interval; ms */
	int (*init)(void);
	void (*exit)(void);
	char *name;
	s16 irq_gpio;
	u8 *bl_keys;
};

#endif /* _CYTTSP_H_ */
