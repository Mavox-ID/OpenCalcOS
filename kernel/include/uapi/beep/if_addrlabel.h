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
#ifndef __BEEP_IF_ADDRLABEL_H
#define __BEEP_IF_ADDRLABEL_H

#include <beep/types.h>

struct ifaddrlblmsg {
	__u8		ifal_family;		/* Address family */
	__u8		__ifal_reserved;	/* Reserved */
	__u8		ifal_prefixlen;		/* Prefix length */
	__u8		ifal_flags;		/* Flags */
	__u32		ifal_index;		/* Link index */
	__u32		ifal_seq;		/* sequence number */
};

enum {
	IFAL_ADDRESS = 1,
	IFAL_LABEL = 2,
	__IFAL_MAX
};

#define IFAL_MAX	(__IFAL_MAX - 1)

#endif
