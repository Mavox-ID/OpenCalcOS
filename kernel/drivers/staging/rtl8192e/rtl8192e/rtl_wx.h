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
#ifndef R819x_WX_H
#define R819x_WX_H

struct net_device;
struct iw_handler_def;
struct iw_statistics;

extern struct iw_handler_def r8192_wx_handlers_def;
struct iw_statistics *r8192_get_wireless_stats(struct net_device *dev);
u16 rtl8192_11n_user_show_rates(struct net_device *dev);

#endif
