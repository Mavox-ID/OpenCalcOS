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
#ifndef _OZAPPIF_H
#define _OZAPPIF_H

#include "ozeventdef.h"

#define OZ_IOCTL_MAGIC	0xf4

struct oz_mac_addr {
	__u8 a[6];
};

#define OZ_MAX_PDS	8

struct oz_pd_list {
	__u32 count;
	struct oz_mac_addr addr[OZ_MAX_PDS];
};

#define OZ_MAX_BINDING_LEN	32

struct oz_binding_info {
	char name[OZ_MAX_BINDING_LEN];
};

#define OZ_IOCTL_GET_PD_LIST	_IOR(OZ_IOCTL_MAGIC, 0, struct oz_pd_list)
#define OZ_IOCTL_SET_ACTIVE_PD	_IOW(OZ_IOCTL_MAGIC, 1, struct oz_mac_addr)
#define OZ_IOCTL_GET_ACTIVE_PD	_IOR(OZ_IOCTL_MAGIC, 2, struct oz_mac_addr)
#define OZ_IOCTL_ADD_BINDING	_IOW(OZ_IOCTL_MAGIC, 3, struct oz_binding_info)
#define OZ_IOCTL_REMOVE_BINDING	_IOW(OZ_IOCTL_MAGIC, 4, struct oz_binding_info)
#define OZ_IOCTL_MAX		5


#endif /* _OZAPPIF_H */
