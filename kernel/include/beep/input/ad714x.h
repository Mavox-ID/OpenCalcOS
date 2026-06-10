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
#ifndef __BEEP_INPUT_AD714X_H__
#define __BEEP_INPUT_AD714X_H__

#define STAGE_NUM              12
#define STAGE_CFGREG_NUM       8
#define SYS_CFGREG_NUM         8

/* board information which need be initialized in arch/mach... */
struct ad714x_slider_plat {
	int start_stage;
	int end_stage;
	int max_coord;
};

struct ad714x_wheel_plat {
	int start_stage;
	int end_stage;
	int max_coord;
};

struct ad714x_touchpad_plat {
	int x_start_stage;
	int x_end_stage;
	int x_max_coord;

	int y_start_stage;
	int y_end_stage;
	int y_max_coord;
};

struct ad714x_button_plat {
	int keycode;
	unsigned short l_mask;
	unsigned short h_mask;
};

struct ad714x_platform_data {
	int slider_num;
	int wheel_num;
	int touchpad_num;
	int button_num;
	struct ad714x_slider_plat *slider;
	struct ad714x_wheel_plat *wheel;
	struct ad714x_touchpad_plat *touchpad;
	struct ad714x_button_plat *button;
	unsigned short stage_cfg_reg[STAGE_NUM][STAGE_CFGREG_NUM];
	unsigned short sys_cfg_reg[SYS_CFGREG_NUM];
	unsigned long irqflags;
};

#endif
