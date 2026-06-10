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
#ifndef _TBLDPASETTING_H_
#define _TBLDPASETTING_H_
#include "global.h"

#define DPA_CLK_30M       30000000
#define DPA_CLK_50M       50000000
#define DPA_CLK_70M       70000000
#define DPA_CLK_100M      100000000
#define DPA_CLK_150M      150000000

enum DPA_RANGE {
	DPA_CLK_RANGE_30M,
	DPA_CLK_RANGE_30_50M,
	DPA_CLK_RANGE_50_70M,
	DPA_CLK_RANGE_70_100M,
	DPA_CLK_RANGE_100_150M,
	DPA_CLK_RANGE_150M
};

extern struct GFX_DPA_SETTING GFX_DPA_SETTING_TBL_VT3324[6];
extern struct GFX_DPA_SETTING GFX_DPA_SETTING_TBL_VT3327[];
extern struct GFX_DPA_SETTING GFX_DPA_SETTING_TBL_VT3364[6];

#endif
