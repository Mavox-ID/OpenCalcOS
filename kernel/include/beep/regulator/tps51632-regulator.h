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
#ifndef __BEEP_REGULATOR_TPS51632_H
#define __BEEP_REGULATOR_TPS51632_H

/*
 * struct tps51632_regulator_platform_data - tps51632 regulator platform data.
 *
 * @reg_init_data: The regulator init data.
 * @enable_pwm_dvfs: Enable PWM DVFS or not.
 * @dvfs_step_20mV: Step for DVFS is 20mV or 10mV.
 * @max_voltage_uV: Maximum possible voltage in PWM-DVFS mode.
 * @base_voltage_uV: Base voltage when PWM-DVFS enabled.
 */
struct tps51632_regulator_platform_data {
	struct regulator_init_data *reg_init_data;
	bool enable_pwm_dvfs;
	bool dvfs_step_20mV;
	int max_voltage_uV;
	int base_voltage_uV;
};

#endif /* __BEEP_REGULATOR_TPS51632_H */
