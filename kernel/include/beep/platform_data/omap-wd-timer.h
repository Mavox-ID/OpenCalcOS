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
#ifndef __BEEP_PLATFORM_DATA_OMAP_WD_TIMER_H
#define __BEEP_PLATFORM_DATA_OMAP_WD_TIMER_H

#include <beep/types.h>

/*
 * Standardized OMAP reset source bits
 *
 * This is a subset of the ones listed in arch/arm/mach-omap2/prm.h
 * and are the only ones needed in the watchdog driver.
 */
#define OMAP_MPU_WD_RST_SRC_ID_SHIFT				3

/**
 * struct omap_wd_timer_platform_data - WDTIMER integration to the host SoC
 * @read_reset_sources - fn ptr for the SoC to indicate the last reset cause
 *
 * The function pointed to by @read_reset_sources must return its data
 * in a standard format - search for RST_SRC_ID_SHIFT in
 * arch/arm/mach-omap2
 */
struct omap_wd_timer_platform_data {
	u32 (*read_reset_sources)(void);
};

#endif
