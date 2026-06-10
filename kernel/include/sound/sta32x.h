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
#ifndef __BEEP_SND__STA32X_H
#define __BEEP_SND__STA32X_H

#define STA32X_OCFG_2CH		0
#define STA32X_OCFG_2_1CH	1
#define STA32X_OCFG_1CH		3

#define STA32X_OM_CH1		0
#define STA32X_OM_CH2		1
#define STA32X_OM_CH3		2

#define STA32X_THERMAL_ADJUSTMENT_ENABLE	1
#define STA32X_THERMAL_RECOVERY_ENABLE		2

struct sta32x_platform_data {
	int output_conf;
	int ch1_output_mapping;
	int ch2_output_mapping;
	int ch3_output_mapping;
	int thermal_conf;
	int needs_esd_watchdog;
};

#endif /* __BEEP_SND__STA32X_H */
