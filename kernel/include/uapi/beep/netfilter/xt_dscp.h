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
#ifndef _XT_DSCP_H
#define _XT_DSCP_H

#include <beep/types.h>

#define XT_DSCP_MASK	0xfc	/* 11111100 */
#define XT_DSCP_SHIFT	2
#define XT_DSCP_MAX	0x3f	/* 00111111 */

/* match info */
struct xt_dscp_info {
	__u8 dscp;
	__u8 invert;
};

struct xt_tos_match_info {
	__u8 tos_mask;
	__u8 tos_value;
	__u8 invert;
};

#endif /* _XT_DSCP_H */
