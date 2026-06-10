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
#ifndef __VIAMODE_H__
#define __VIAMODE_H__

#include "global.h"

struct VPITTable {
	unsigned char Misc;
	unsigned char SR[StdSR];
	unsigned char GR[StdGR];
	unsigned char AR[StdAR];
};

struct patch_table {
	int table_length;
	struct io_reg *io_reg_table;
};

extern int NUM_TOTAL_CN400_ModeXregs;
extern int NUM_TOTAL_CN700_ModeXregs;
extern int NUM_TOTAL_KM400_ModeXregs;
extern int NUM_TOTAL_CX700_ModeXregs;
extern int NUM_TOTAL_VX855_ModeXregs;
extern int NUM_TOTAL_CLE266_ModeXregs;
extern int NUM_TOTAL_PATCH_MODE;

extern struct io_reg CN400_ModeXregs[];
extern struct io_reg CN700_ModeXregs[];
extern struct io_reg KM400_ModeXregs[];
extern struct io_reg CX700_ModeXregs[];
extern struct io_reg VX800_ModeXregs[];
extern struct io_reg VX855_ModeXregs[];
extern struct io_reg CLE266_ModeXregs[];
extern struct io_reg PM1024x768[];
extern struct patch_table res_patch_table[];
extern struct VPITTable VPIT;

const struct fb_videomode *viafb_get_best_mode(int hres, int vres,
	int refresh);
const struct fb_videomode *viafb_get_best_rb_mode(int hres, int vres,
	int refresh);

#endif /* __VIAMODE_H__ */
