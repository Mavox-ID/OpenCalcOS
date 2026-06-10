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
#ifndef __BEEP_REGULATOR_MAX8649_H
#define	__BEEP_REGULATOR_MAX8649_H

#include <beep/regulator/machine.h>

enum {
	MAX8649_EXTCLK_26MHZ = 0,
	MAX8649_EXTCLK_13MHZ,
	MAX8649_EXTCLK_19MHZ,	/* 19.2MHz */
};

enum {
	MAX8649_RAMP_32MV = 0,
	MAX8649_RAMP_16MV,
	MAX8649_RAMP_8MV,
	MAX8649_RAMP_4MV,
	MAX8649_RAMP_2MV,
	MAX8649_RAMP_1MV,
	MAX8649_RAMP_0_5MV,
	MAX8649_RAMP_0_25MV,
};

struct max8649_platform_data {
	struct regulator_init_data *regulator;

	unsigned	mode:2;		/* bit[1:0] = VID1,VID0 */
	unsigned	extclk_freq:2;
	unsigned	extclk:1;
	unsigned	ramp_timing:3;
	unsigned	ramp_down:1;
};

#endif	/* __BEEP_REGULATOR_MAX8649_H */
