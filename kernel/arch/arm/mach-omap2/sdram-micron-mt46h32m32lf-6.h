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
#ifndef ARCH_ARM_MACH_OMAP2_SDRAM_MICRON_MT46H32M32LF
#define ARCH_ARM_MACH_OMAP2_SDRAM_MICRON_MT46H32M32LF

#include "sdrc.h"

/* Micron MT46H32M32LF-6 */
/* XXX Using ARE = 0x1 (no autorefresh burst) -- can this be changed? */
static struct omap_sdrc_params mt46h32m32lf6_sdrc_params[] = {
	[0] = {
		.rate	     = 166000000,
		.actim_ctrla = 0x9a9db4c6,
		.actim_ctrlb = 0x00011217,
		.rfr_ctrl    = 0x0004dc01,
		.mr	     = 0x00000032,
	},
	[1] = {
		.rate	     = 165941176,
		.actim_ctrla = 0x9a9db4c6,
		.actim_ctrlb = 0x00011217,
		.rfr_ctrl    = 0x0004dc01,
		.mr	     = 0x00000032,
	},
	[2] = {
		.rate	     = 83000000,
		.actim_ctrla = 0x51512283,
		.actim_ctrlb = 0x0001120c,
		.rfr_ctrl    = 0x00025501,
		.mr	     = 0x00000032,
	},
	[3] = {
		.rate	     = 82970588,
		.actim_ctrla = 0x51512283,
		.actim_ctrlb = 0x0001120c,
		.rfr_ctrl    = 0x00025501,
		.mr	     = 0x00000032,
	},
	[4] = {
		.rate	     = 0
	},
};

#endif
