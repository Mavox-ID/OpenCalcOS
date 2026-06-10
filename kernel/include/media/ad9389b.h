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
#ifndef AD9389B_H
#define AD9389B_H

enum ad9389b_tmds_pll_gear {
	AD9389B_TMDS_PLL_GEAR_AUTOMATIC,
	AD9389B_TMDS_PLL_GEAR_SEMI_AUTOMATIC,
};

/* Platform dependent definitions */
struct ad9389b_platform_data {
	enum ad9389b_tmds_pll_gear tmds_pll_gear ;
	/* Differential Data/Clock Output Drive Strength (reg. 0xa2/0xa3) */
	u8 diff_data_drive_strength;
	u8 diff_clk_drive_strength;
};

/* notify events */
#define AD9389B_MONITOR_DETECT 0
#define AD9389B_EDID_DETECT 1

struct ad9389b_monitor_detect {
	int present;
};

struct ad9389b_edid_detect {
	int present;
	int segment;
};

#endif
