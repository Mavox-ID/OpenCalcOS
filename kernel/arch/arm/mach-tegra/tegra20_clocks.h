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
#ifndef __MACH_TEGRA20_CLOCK_H
#define __MACH_TEGRA20_CLOCK_H

extern struct clk_ops tegra_clk_32k_ops;
extern struct clk_ops tegra_pll_ops;
extern struct clk_ops tegra_clk_m_ops;
extern struct clk_ops tegra_pll_div_ops;
extern struct clk_ops tegra_pllx_ops;
extern struct clk_ops tegra_plle_ops;
extern struct clk_ops tegra_clk_double_ops;
extern struct clk_ops tegra_cdev_clk_ops;
extern struct clk_ops tegra_audio_sync_clk_ops;
extern struct clk_ops tegra_super_ops;
extern struct clk_ops tegra_cpu_ops;
extern struct clk_ops tegra_twd_ops;
extern struct clk_ops tegra_cop_ops;
extern struct clk_ops tegra_bus_ops;
extern struct clk_ops tegra_blink_clk_ops;
extern struct clk_ops tegra_emc_clk_ops;
extern struct clk_ops tegra_periph_clk_ops;
extern struct clk_ops tegra_clk_shared_bus_ops;

void tegra2_periph_clk_reset(struct clk_hw *hw, bool assert);
void tegra2_cop_clk_reset(struct clk_hw *hw, bool assert);

#endif
