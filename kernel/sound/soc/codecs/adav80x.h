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
#ifndef _ADAV80X_H
#define _ADAV80X_H

enum adav80x_pll_src {
	ADAV80X_PLL_SRC_XIN,
	ADAV80X_PLL_SRC_XTAL,
	ADAV80X_PLL_SRC_MCLKI,
};

enum adav80x_pll {
	ADAV80X_PLL1 = 0,
	ADAV80X_PLL2 = 1,
};

enum adav80x_clk_src {
	ADAV80X_CLK_XIN = 0,
	ADAV80X_CLK_MCLKI = 1,
	ADAV80X_CLK_PLL1 = 2,
	ADAV80X_CLK_PLL2 = 3,
	ADAV80X_CLK_XTAL = 6,

	ADAV80X_CLK_SYSCLK1 = 6,
	ADAV80X_CLK_SYSCLK2 = 7,
	ADAV80X_CLK_SYSCLK3 = 8,
};

#endif
