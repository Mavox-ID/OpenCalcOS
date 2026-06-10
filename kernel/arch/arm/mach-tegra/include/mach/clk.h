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
#ifndef __MACH_CLK_H
#define __MACH_CLK_H

struct clk;

enum tegra_clk_ex_param {
	TEGRA_CLK_VI_INP_SEL,
	TEGRA_CLK_DTV_INVERT,
	TEGRA_CLK_NAND_PAD_DIV2_ENB,
	TEGRA_CLK_PLLD_CSI_OUT_ENB,
	TEGRA_CLK_PLLD_DSI_OUT_ENB,
	TEGRA_CLK_PLLD_MIPI_MUX_SEL,
};

void tegra_periph_reset_deassert(struct clk *c);
void tegra_periph_reset_assert(struct clk *c);

#ifndef CONFIG_COMMON_CLK
unsigned long clk_get_rate_all_locked(struct clk *c);
#endif

void tegra2_sdmmc_tap_delay(struct clk *c, int delay);
int tegra_clk_cfg_ex(struct clk *c, enum tegra_clk_ex_param p, u32 setting);

#endif
