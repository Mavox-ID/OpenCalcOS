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
#ifndef __WL1251_PS_H__
#define __WL1251_PS_H__

#include "wl1251.h"
#include "acx.h"

int wl1251_ps_set_mode(struct wl1251 *wl, enum wl1251_station_mode mode);
void wl1251_ps_elp_sleep(struct wl1251 *wl);
int wl1251_ps_elp_wakeup(struct wl1251 *wl);
void wl1251_elp_work(struct work_struct *work);


#endif /* __WL1251_PS_H__ */
