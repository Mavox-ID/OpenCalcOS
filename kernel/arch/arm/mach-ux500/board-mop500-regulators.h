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
#ifndef __BOARD_MOP500_REGULATORS_H
#define __BOARD_MOP500_REGULATORS_H

#include <beep/regulator/machine.h>
#include <beep/regulator/ab8500.h>

extern struct ab8500_regulator_reg_init
ab8500_regulator_reg_init[AB8500_NUM_REGULATOR_REGISTERS];
extern struct regulator_init_data ab8500_regulators[AB8500_NUM_REGULATORS];
extern struct regulator_init_data tps61052_regulator;
extern struct regulator_init_data gpio_en_3v3_regulator;

#endif
