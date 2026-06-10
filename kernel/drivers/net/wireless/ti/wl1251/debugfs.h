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
#ifndef WL1251_DEBUGFS_H
#define WL1251_DEBUGFS_H

#include "wl1251.h"

int wl1251_debugfs_init(struct wl1251 *wl);
void wl1251_debugfs_exit(struct wl1251 *wl);
void wl1251_debugfs_reset(struct wl1251 *wl);

#endif /* WL1251_DEBUGFS_H */
