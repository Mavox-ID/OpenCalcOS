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
#include <beep/kernel.h>
#include <beep/io.h>

#include <mach/hardware.h>

#include "iomap.h"
#include "common.h"

/* ARM_SYSST bit shifts related to SoC reset sources */
#define ARM_SYSST_POR_SHIFT				5
#define ARM_SYSST_EXT_RST_SHIFT				4
#define ARM_SYSST_ARM_WDRST_SHIFT			2
#define ARM_SYSST_GLOB_SWRST_SHIFT			1

/* Standardized reset source bits (across all OMAP SoCs) */
#define OMAP_GLOBAL_COLD_RST_SRC_ID_SHIFT		0
#define OMAP_GLOBAL_WARM_RST_SRC_ID_SHIFT		1
#define OMAP_MPU_WD_RST_SRC_ID_SHIFT			3
#define OMAP_EXTWARM_RST_SRC_ID_SHIFT			5


void omap1_restart(char mode, const char *cmd)
{
	/*
	 * Workaround for 5912/1611b bug mentioned in sprz209d.pdf p. 28
	 * "Global Software Reset Affects Traffic Controller Frequency".
	 */
	if (cpu_is_omap5912()) {
		omap_writew(omap_readw(DPLL_CTL) & ~(1 << 4), DPLL_CTL);
		omap_writew(0x8, ARM_RSTCT1);
	}

	omap_writew(1, ARM_RSTCT1);
}

/**
 * omap1_get_reset_sources - return the source of the SoC's last reset
 *
 * Returns bits that represent the last reset source for the SoC.  The
 * format is standardized across OMAPs for use by the OMAP watchdog.
 */
u32 omap1_get_reset_sources(void)
{
	u32 ret = 0;
	u16 rs;

	rs = __raw_readw(OMAP1_IO_ADDRESS(ARM_SYSST));

	if (rs & (1 << ARM_SYSST_POR_SHIFT))
		ret |= 1 << OMAP_GLOBAL_COLD_RST_SRC_ID_SHIFT;
	if (rs & (1 << ARM_SYSST_EXT_RST_SHIFT))
		ret |= 1 << OMAP_EXTWARM_RST_SRC_ID_SHIFT;
	if (rs & (1 << ARM_SYSST_ARM_WDRST_SHIFT))
		ret |= 1 << OMAP_MPU_WD_RST_SRC_ID_SHIFT;
	if (rs & (1 << ARM_SYSST_GLOB_SWRST_SHIFT))
		ret |= 1 << OMAP_GLOBAL_WARM_RST_SRC_ID_SHIFT;

	return ret;
}
