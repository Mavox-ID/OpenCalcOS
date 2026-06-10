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
#ifndef __OSD_TYPES_H__
#define __OSD_TYPES_H__

struct osd_systemid {
	u8 data[OSD_SYSTEMID_LEN];
};

typedef u64 __bitwise osd_id;

struct osd_obj_id {
	osd_id partition;
	osd_id id;
};

static const struct __weak osd_obj_id osd_root_object = {0, 0};

struct osd_attr {
	u32 attr_page;
	u32 attr_id;
	u16 len;		/* byte count of operand */
	void *val_ptr;		/* in network order */
};

struct osd_sg_entry {
	u64 offset;
	u64 len;
};

#endif /* ndef __OSD_TYPES_H__ */
