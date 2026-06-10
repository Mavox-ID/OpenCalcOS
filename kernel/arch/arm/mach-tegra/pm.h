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
#ifndef _MACH_TEGRA_PM_H_
#define _MACH_TEGRA_PM_H_

extern unsigned long l2x0_saved_regs_addr;

void save_cpu_arch_register(void);
void restore_cpu_arch_register(void);

void tegra_clear_cpu_in_lp2(int phy_cpu_id);
bool tegra_set_cpu_in_lp2(int phy_cpu_id);

void tegra_idle_lp2_last(u32 cpu_on_time, u32 cpu_off_time);
extern void (*tegra_tear_down_cpu)(void);

#endif /* _MACH_TEGRA_PM_H_ */
