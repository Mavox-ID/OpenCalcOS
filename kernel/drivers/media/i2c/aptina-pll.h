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
#ifndef __APTINA_PLL_H
#define __APTINA_PLL_H

struct aptina_pll {
	unsigned int ext_clock;
	unsigned int pix_clock;

	unsigned int n;
	unsigned int m;
	unsigned int p1;
};

struct aptina_pll_limits {
	unsigned int ext_clock_min;
	unsigned int ext_clock_max;
	unsigned int int_clock_min;
	unsigned int int_clock_max;
	unsigned int out_clock_min;
	unsigned int out_clock_max;
	unsigned int pix_clock_max;

	unsigned int n_min;
	unsigned int n_max;
	unsigned int m_min;
	unsigned int m_max;
	unsigned int p1_min;
	unsigned int p1_max;
};

struct device;

int aptina_pll_calculate(struct device *dev,
			 const struct aptina_pll_limits *limits,
			 struct aptina_pll *pll);

#endif /* __APTINA_PLL_H */
