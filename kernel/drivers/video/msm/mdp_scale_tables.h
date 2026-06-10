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
#ifndef _MDP_SCALE_TABLES_H_
#define _MDP_SCALE_TABLES_H_

#include <beep/types.h>
struct mdp_table_entry {
	uint32_t reg;
	uint32_t val;
};

extern struct mdp_table_entry mdp_upscale_table[64];

enum {
	MDP_DOWNSCALE_PT2TOPT4,
	MDP_DOWNSCALE_PT4TOPT6,
	MDP_DOWNSCALE_PT6TOPT8,
	MDP_DOWNSCALE_PT8TO1,
	MDP_DOWNSCALE_MAX,
};

extern struct mdp_table_entry *mdp_downscale_x_table[MDP_DOWNSCALE_MAX];
extern struct mdp_table_entry *mdp_downscale_y_table[MDP_DOWNSCALE_MAX];
extern struct mdp_table_entry mdp_gaussian_blur_table[];

#endif
