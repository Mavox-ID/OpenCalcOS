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
#ifndef _MACH_TEGRA_POWERGATE_H_
#define _MACH_TEGRA_POWERGATE_H_

struct clk;

#define TEGRA_POWERGATE_CPU	0
#define TEGRA_POWERGATE_3D	1
#define TEGRA_POWERGATE_VENC	2
#define TEGRA_POWERGATE_PCIE	3
#define TEGRA_POWERGATE_VDEC	4
#define TEGRA_POWERGATE_L2	5
#define TEGRA_POWERGATE_MPE	6
#define TEGRA_POWERGATE_HEG	7
#define TEGRA_POWERGATE_SATA	8
#define TEGRA_POWERGATE_CPU1	9
#define TEGRA_POWERGATE_CPU2	10
#define TEGRA_POWERGATE_CPU3	11
#define TEGRA_POWERGATE_CELP	12
#define TEGRA_POWERGATE_3D1	13

#define TEGRA_POWERGATE_CPU0	TEGRA_POWERGATE_CPU
#define TEGRA_POWERGATE_3D0	TEGRA_POWERGATE_3D

int  __init tegra_powergate_init(void);

int tegra_cpu_powergate_id(int cpuid);
int tegra_powergate_is_powered(int id);
int tegra_powergate_power_on(int id);
int tegra_powergate_power_off(int id);
int tegra_powergate_remove_clamping(int id);

/* Must be called with clk disabled, and returns with clk enabled */
int tegra_powergate_sequence_power_up(int id, struct clk *clk);

#endif /* _MACH_TEGRA_POWERGATE_H_ */
