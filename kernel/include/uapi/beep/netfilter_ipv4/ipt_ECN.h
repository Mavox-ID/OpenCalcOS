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
#ifndef _IPT_ECN_TARGET_H
#define _IPT_ECN_TARGET_H

#include <beep/types.h>
#include <beep/netfilter/xt_DSCP.h>

#define IPT_ECN_IP_MASK	(~XT_DSCP_MASK)

#define IPT_ECN_OP_SET_IP	0x01	/* set ECN bits of IPv4 header */
#define IPT_ECN_OP_SET_ECE	0x10	/* set ECE bit of TCP header */
#define IPT_ECN_OP_SET_CWR	0x20	/* set CWR bit of TCP header */

#define IPT_ECN_OP_MASK		0xce

struct ipt_ECN_info {
	__u8 operation;	/* bitset of operations */
	__u8 ip_ect;	/* ECT codepoint of IPv4 header, pre-shifted */
	union {
		struct {
			__u8 ece:1, cwr:1; /* TCP ECT bits */
		} tcp;
	} proto;
};

#endif /* _IPT_ECN_TARGET_H */
