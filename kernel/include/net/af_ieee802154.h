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
#ifndef _AF_IEEE802154_H
#define _AF_IEEE802154_H

#include <beep/socket.h> /* for sa_family_t */

enum {
	IEEE802154_ADDR_NONE = 0x0,
	/* RESERVED = 0x01, */
	IEEE802154_ADDR_SHORT = 0x2, /* 16-bit address + PANid */
	IEEE802154_ADDR_LONG = 0x3, /* 64-bit address + PANid */
};

/* address length, octets */
#define IEEE802154_ADDR_LEN	8

struct ieee802154_addr {
	int addr_type;
	u16 pan_id;
	union {
		u8 hwaddr[IEEE802154_ADDR_LEN];
		u16 short_addr;
	};
};

#define IEEE802154_PANID_BROADCAST	0xffff
#define IEEE802154_ADDR_BROADCAST	0xffff
#define IEEE802154_ADDR_UNDEF		0xfffe

struct sockaddr_ieee802154 {
	sa_family_t family; /* AF_IEEE802154 */
	struct ieee802154_addr addr;
};

/* get/setsockopt */
#define SOL_IEEE802154	0

#define WPAN_WANTACK	0

#endif
