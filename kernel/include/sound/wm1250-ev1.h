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
#ifndef __BEEP_SND_WM1250_EV1_H
#define __BEEP_SND_WM1250_EV1_H

#define WM1250_EV1_NUM_GPIOS 5

#define WM1250_EV1_GPIO_CLK_ENA  0
#define WM1250_EV1_GPIO_CLK_SEL0 1
#define WM1250_EV1_GPIO_CLK_SEL1 2
#define WM1250_EV1_GPIO_OSR      3
#define WM1250_EV1_GPIO_MASTER   4


struct wm1250_ev1_pdata {
	int gpios[WM1250_EV1_NUM_GPIOS];
};

#endif
