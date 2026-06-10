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
#ifndef _UAPINFS_IDMAP_H
#define _UAPINFS_IDMAP_H

#include <beep/types.h>

/* XXX from bits/utmp.h  */
#define IDMAP_NAMESZ  128

#define IDMAP_TYPE_USER  0
#define IDMAP_TYPE_GROUP 1

#define IDMAP_CONV_IDTONAME 0
#define IDMAP_CONV_NAMETOID 1

#define IDMAP_STATUS_INVALIDMSG 0x01
#define IDMAP_STATUS_AGAIN      0x02
#define IDMAP_STATUS_LOOKUPFAIL 0x04
#define IDMAP_STATUS_SUCCESS    0x08

struct idmap_msg {
	__u8  im_type;
	__u8  im_conv;
	char  im_name[IDMAP_NAMESZ];
	__u32 im_id;
	__u8  im_status;
};


#endif /* _UAPINFS_IDMAP_H */
