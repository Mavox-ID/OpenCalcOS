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
#ifndef __TEGRA_ASOC_UTILS_H__
#define __TEGRA_ASOC_UTILS_H_

struct clk;
struct device;

enum tegra_asoc_utils_soc {
	TEGRA_ASOC_UTILS_SOC_TEGRA20,
	TEGRA_ASOC_UTILS_SOC_TEGRA30,
};

struct tegra_asoc_utils_data {
	struct device *dev;
	enum tegra_asoc_utils_soc soc;
	struct clk *clk_pll_a;
	struct clk *clk_pll_a_out0;
	struct clk *clk_cdev1;
	int set_baseclock;
	int set_mclk;
};

int tegra_asoc_utils_set_rate(struct tegra_asoc_utils_data *data, int srate,
			      int mclk);
int tegra_asoc_utils_init(struct tegra_asoc_utils_data *data,
			  struct device *dev);
void tegra_asoc_utils_fini(struct tegra_asoc_utils_data *data);

#endif
