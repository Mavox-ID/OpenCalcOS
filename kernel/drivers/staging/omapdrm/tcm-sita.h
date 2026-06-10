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
#ifndef _TCM_SITA_H
#define _TCM_SITA_H

#include "tcm.h"

/* length between two coordinates */
#define LEN(a, b) ((a) > (b) ? (a) - (b) + 1 : (b) - (a) + 1)

enum criteria {
	CR_MAX_NEIGHS		= 0x01,
	CR_FIRST_FOUND		= 0x10,
	CR_BIAS_HORIZONTAL	= 0x20,
	CR_BIAS_VERTICAL	= 0x40,
	CR_DIAGONAL_BALANCE	= 0x80
};

/* nearness to the beginning of the search field from 0 to 1000 */
struct nearness_factor {
	s32 x;
	s32 y;
};

/*
 * Statistics on immediately neighboring slots.  Edge is the number of
 * border segments that are also border segments of the scan field.  Busy
 * refers to the number of neighbors that are occupied.
 */
struct neighbor_stats {
	u16 edge;
	u16 busy;
};

/* structure to keep the score of a potential allocation */
struct score {
	struct nearness_factor	f;
	struct neighbor_stats	n;
	struct tcm_area		a;
	u16    neighs;		/* number of busy neighbors */
};

struct sita_pvt {
	spinlock_t lock;	/* spinlock to protect access */
	struct tcm_pt div_pt;	/* divider point splitting container */
	struct tcm_area ***map;	/* pointers to the parent area for each slot */
};

/* assign coordinates to area */
static inline
void assign(struct tcm_area *a, u16 x0, u16 y0, u16 x1, u16 y1)
{
	a->p0.x = x0;
	a->p0.y = y0;
	a->p1.x = x1;
	a->p1.y = y1;
}

#endif
