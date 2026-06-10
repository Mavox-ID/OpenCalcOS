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
#define ANT_SWCTRL_TBL_REV3_IDX (0)

#include <types.h>
#include "phy_int.h"

extern const struct phytbl_info mimophytbl_info_rev0[],
				mimophytbl_info_rev0_volatile[];

extern const u32 mimophytbl_info_sz_rev0,
		 mimophytbl_info_sz_rev0_volatile;

extern const struct phytbl_info mimophytbl_info_rev3[],
				mimophytbl_info_rev3_volatile[],
				mimophytbl_info_rev3_volatile1[],
				mimophytbl_info_rev3_volatile2[],
				mimophytbl_info_rev3_volatile3[];

extern const u32 mimophytbl_info_sz_rev3,
		 mimophytbl_info_sz_rev3_volatile,
		 mimophytbl_info_sz_rev3_volatile1,
		 mimophytbl_info_sz_rev3_volatile2,
		 mimophytbl_info_sz_rev3_volatile3;

extern const u32 noise_var_tbl_rev3[];

extern const struct phytbl_info mimophytbl_info_rev7[];

extern const u32 mimophytbl_info_sz_rev7;

extern const u32 noise_var_tbl_rev7[];

extern const struct phytbl_info mimophytbl_info_rev16[];

extern const u32 mimophytbl_info_sz_rev16;
