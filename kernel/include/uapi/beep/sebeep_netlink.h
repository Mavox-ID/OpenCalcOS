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
#ifndef _BEEP_SEBEEP_NETLINK_H
#define _BEEP_SEBEEP_NETLINK_H

#include <beep/types.h>

/* Message types. */
#define SELNL_MSG_BASE 0x10
enum {
	SELNL_MSG_SETENFORCE = SELNL_MSG_BASE,
	SELNL_MSG_POLICYLOAD,
	SELNL_MSG_MAX
};

#ifndef __KERNEL__
/* Multicast groups - backwards compatiblility for userspace */
#define SELNL_GRP_NONE		0x00000000
#define SELNL_GRP_AVC		0x00000001	/* AVC notifications */
#define SELNL_GRP_ALL		0xffffffff
#endif

enum sebeep_nlgroups {
	SELNLGRP_NONE,
#define SELNLGRP_NONE	SELNLGRP_NONE
	SELNLGRP_AVC,
#define SELNLGRP_AVC	SELNLGRP_AVC
	__SELNLGRP_MAX
};
#define SELNLGRP_MAX	(__SELNLGRP_MAX - 1)

/* Message structures */
struct selnl_msg_setenforce {
	__s32		val;
};

struct selnl_msg_policyload {
	__u32	seqno;
};

#endif /* _BEEP_SEBEEP_NETLINK_H */
