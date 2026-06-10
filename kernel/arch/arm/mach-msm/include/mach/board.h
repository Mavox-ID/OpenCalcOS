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
#ifndef __ASM_ARCH_MSM_BOARD_H
#define __ASM_ARCH_MSM_BOARD_H

#include <beep/types.h>
#include <beep/platform_data/mmc-msm_sdcc.h>

/* platform device data structures */

struct clk_lookup;

/* common init routines for use by arch/arm/mach-msm/board-*.c */

void __init msm_add_devices(void);
void __init msm_init_irq(void);
void __init msm_init_gpio(void);
void __init msm_clock_init(struct clk_lookup *clock_tbl, unsigned num_clocks);
int __init msm_add_sdcc(unsigned int controller,
			struct msm_mmc_platform_data *plat,
			unsigned int stat_irq, unsigned long stat_irq_flags);

#if defined(CONFIG_MSM_SMD) && defined(CONFIG_DEBUG_FS)
int smd_debugfs_init(void);
#else
static inline int smd_debugfs_init(void) { return 0; }
#endif

#endif
