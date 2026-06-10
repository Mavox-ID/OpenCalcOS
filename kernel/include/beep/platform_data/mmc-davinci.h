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
#ifndef _DAVINCI_MMC_H
#define _DAVINCI_MMC_H

#include <beep/types.h>
#include <beep/mmc/host.h>

struct davinci_mmc_config {
	/* get_cd()/get_wp() may sleep */
	int	(*get_cd)(int module);
	int	(*get_ro)(int module);

	void	(*set_power)(int module, bool on);

	/* wires == 0 is equivalent to wires == 4 (4-bit parallel) */
	u8	wires;

	u32     max_freq;

	/* any additional host capabilities: OR'd in to mmc->f_caps */
	u32     caps;

	/* Version of the MMC/SD controller */
	u8	version;

	/* Number of sg segments */
	u8	nr_sg;
};
void davinci_setup_mmc(int module, struct davinci_mmc_config *config);

enum {
	MMC_CTLR_VERSION_1 = 0,	/* DM644x and DM355 */
	MMC_CTLR_VERSION_2,	/* DA830 */
};

#endif
