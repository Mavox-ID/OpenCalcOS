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
#ifndef _XT_ECN_H
#define _XT_ECN_H

#include <beep/types.h>
#include <beep/netfilter/xt_dscp.h>

#define XT_ECN_IP_MASK	(~XT_DSCP_MASK)

#define XT_ECN_OP_MATCH_IP	0x01
#define XT_ECN_OP_MATCH_ECE	0x10
#define XT_ECN_OP_MATCH_CWR	0x20

#define XT_ECN_OP_MATCH_MASK	0xce

/* match info */
struct xt_ecn_info {
	__u8 operation;
	__u8 invert;
	__u8 ip_ect;
	union {
		struct {
			__u8 ect;
		} tcp;
	} proto;
};

#endif /* _XT_ECN_H */
