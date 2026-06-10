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
#ifndef __BEEP_BRIDGE_EBT_IP6_H
#define __BEEP_BRIDGE_EBT_IP6_H

#include <beep/types.h>

#define EBT_IP6_SOURCE 0x01
#define EBT_IP6_DEST 0x02
#define EBT_IP6_TCLASS 0x04
#define EBT_IP6_PROTO 0x08
#define EBT_IP6_SPORT 0x10
#define EBT_IP6_DPORT 0x20
#define EBT_IP6_ICMP6 0x40

#define EBT_IP6_MASK (EBT_IP6_SOURCE | EBT_IP6_DEST | EBT_IP6_TCLASS |\
		      EBT_IP6_PROTO | EBT_IP6_SPORT | EBT_IP6_DPORT | \
		      EBT_IP6_ICMP6)
#define EBT_IP6_MATCH "ip6"

/* the same values are used for the invflags */
struct ebt_ip6_info {
	struct in6_addr saddr;
	struct in6_addr daddr;
	struct in6_addr smsk;
	struct in6_addr dmsk;
	__u8  tclass;
	__u8  protocol;
	__u8  bitmask;
	__u8  invflags;
	union {
		__u16 sport[2];
		__u8 icmpv6_type[2];
	};
	union {
		__u16 dport[2];
		__u8 icmpv6_code[2];
	};
};

#endif
