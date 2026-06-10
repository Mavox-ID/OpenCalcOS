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
#ifndef __BEEP_REGULATOR_TPS62360_H
#define __BEEP_REGULATOR_TPS62360_H

/*
 * struct tps62360_regulator_platform_data - tps62360 regulator platform data.
 *
 * @reg_init_data: The regulator init data.
 * @en_discharge: Enable discharge the output capacitor via internal
 *                register.
 * @en_internal_pulldn: internal pull down enable or not.
 * @vsel0_gpio: Gpio number for vsel0. It should be -1 if this is tied with
 *              fixed logic.
 * @vsel1_gpio: Gpio number for vsel1. It should be -1 if this is tied with
 *              fixed logic.
 * @vsel0_def_state: Default state of vsel0. 1 if it is high else 0.
 * @vsel1_def_state: Default state of vsel1. 1 if it is high else 0.
 */
struct tps62360_regulator_platform_data {
	struct regulator_init_data *reg_init_data;
	bool en_discharge;
	bool en_internal_pulldn;
	int vsel0_gpio;
	int vsel1_gpio;
	int vsel0_def_state;
	int vsel1_def_state;
};

#endif /* __BEEP_REGULATOR_TPS62360_H */
