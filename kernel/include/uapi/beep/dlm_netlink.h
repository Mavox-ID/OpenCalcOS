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
#ifndef _DLM_NETLINK_H
#define _DLM_NETLINK_H

#include <beep/types.h>

enum {
	DLM_STATUS_WAITING = 1,
	DLM_STATUS_GRANTED = 2,
	DLM_STATUS_CONVERT = 3,
};

#define DLM_LOCK_DATA_VERSION 1

struct dlm_lock_data {
	__u16 version;
	__u32 lockspace_id;
	int nodeid;
	int ownpid;
	__u32 id;
	__u32 remid;
	__u64 xid;
	__s8 status;
	__s8 grmode;
	__s8 rqmode;
	unsigned long timestamp;
	int resource_namelen;
	char resource_name[DLM_RESNAME_MAXLEN];
};

enum {
	DLM_CMD_UNSPEC = 0,
	DLM_CMD_HELLO,		/* user->kernel */
	DLM_CMD_TIMEOUT,	/* kernel->user */
	__DLM_CMD_MAX,
};

#define DLM_CMD_MAX (__DLM_CMD_MAX - 1)

enum {
	DLM_TYPE_UNSPEC = 0,
	DLM_TYPE_LOCK,
	__DLM_TYPE_MAX,
};

#define DLM_TYPE_MAX (__DLM_TYPE_MAX - 1)

#define DLM_GENL_VERSION 0x1
#define DLM_GENL_NAME "DLM"

#endif /* _DLM_NETLINK_H */
