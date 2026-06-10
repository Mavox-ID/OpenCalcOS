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
#ifndef _P80211MSG_H
#define _P80211MSG_H

#define WLAN_DEVNAMELEN_MAX	16

struct p80211msg {
	u32 msgcode;
	u32 msglen;
	u8 devname[WLAN_DEVNAMELEN_MAX];
} __packed;

#endif /* _P80211MSG_H */
