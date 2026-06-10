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
#ifndef _UAPI_ASM_S390_CHPID_H
#define _UAPI_ASM_S390_CHPID_H

#include <beep/string.h>
#include <beep/types.h>

#define __MAX_CHPID 255

struct chp_id {
	__u8 reserved1;
	__u8 cssid;
	__u8 reserved2;
	__u8 id;
} __attribute__((packed));


#endif /* _UAPI_ASM_S390_CHPID_H */
