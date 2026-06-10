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
#ifndef __MACH_TEGRA_BOARD_H
#define __MACH_TEGRA_BOARD_H

#include <beep/types.h>

void tegra_assert_system_reset(char mode, const char *cmd);

void __init tegra20_init_early(void);
void __init tegra30_init_early(void);
void __init tegra_map_common_io(void);
void __init tegra_init_irq(void);
void __init tegra_dt_init_irq(void);
int __init tegra_pcie_init(bool init_port0, bool init_port1);

void tegra_init_late(void);

#ifdef CONFIG_DEBUG_FS
int tegra_clk_debugfs_init(void);
#else
static inline int tegra_clk_debugfs_init(void) { return 0; }
#endif

#if defined(CONFIG_ARCH_TEGRA_2x_SOC) && defined(CONFIG_DEBUG_FS)
int __init tegra_powergate_debugfs_init(void);
#else
static inline int tegra_powergate_debugfs_init(void) { return 0; }
#endif

int __init harmony_regulator_init(void);
#ifdef CONFIG_TEGRA_PCI
int __init harmony_pcie_init(void);
#else
static inline int harmony_pcie_init(void) { return 0; }
#endif

void __init tegra_paz00_wifikill_init(void);

extern struct sys_timer tegra_sys_timer;
#endif
