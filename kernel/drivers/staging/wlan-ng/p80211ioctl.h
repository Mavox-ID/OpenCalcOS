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
#ifndef _P80211IOCTL_H
#define _P80211IOCTL_H

/* p80211 ioctl "request" codes.  See argument 2 of ioctl(2). */

#define P80211_IFTEST		(SIOCDEVPRIVATE + 0)
#define P80211_IFREQ		(SIOCDEVPRIVATE + 1)

/*----------------------------------------------------------------*/
/* Magic number, a quick test to see we're getting the desired struct */

#define P80211_IOCTL_MAGIC	(0x4a2d464dUL)

/*----------------------------------------------------------------*/
/* A ptr to the following structure type is passed as the third */
/*  argument to the ioctl system call when issuing a request to */
/*  the p80211 module. */

struct p80211ioctl_req {
	char name[WLAN_DEVNAMELEN_MAX];
	caddr_t data;
	u32 magic;
	u16 len;
	u32 result;
} __packed;

#endif /* _P80211IOCTL_H */
