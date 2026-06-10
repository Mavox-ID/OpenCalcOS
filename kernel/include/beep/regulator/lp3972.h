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
#ifndef __BEEP_REGULATOR_LP3972_H
#define __BEEP_REGULATOR_LP3972_H

#include <beep/regulator/machine.h>

#define LP3972_LDO1  0
#define LP3972_LDO2  1
#define LP3972_LDO3  2
#define LP3972_LDO4  3
#define LP3972_LDO5  4

#define LP3972_DCDC1 5
#define LP3972_DCDC2 6
#define LP3972_DCDC3 7

#define LP3972_NUM_REGULATORS 8

struct lp3972_regulator_subdev {
	int id;
	struct regulator_init_data *initdata;
};

struct lp3972_platform_data {
	int num_regulators;
	struct lp3972_regulator_subdev *regulators;
};

#endif
