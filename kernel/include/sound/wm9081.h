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
#ifndef __BEEP_SND_WM_9081_H
#define __BEEP_SND_WM_9081_H

struct wm9081_retune_mobile_setting {
	const char *name;
	unsigned int rate;
	u16 config[20];
};

struct wm9081_pdata {
	bool irq_high;   /* IRQ is active high */
	bool irq_cmos;   /* IRQ is in CMOS mode */

	struct wm9081_retune_mobile_setting *retune_configs;
	int num_retune_configs;
};

#endif
