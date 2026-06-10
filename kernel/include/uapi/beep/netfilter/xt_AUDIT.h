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
#ifndef _XT_AUDIT_TARGET_H
#define _XT_AUDIT_TARGET_H

#include <beep/types.h>

enum {
	XT_AUDIT_TYPE_ACCEPT = 0,
	XT_AUDIT_TYPE_DROP,
	XT_AUDIT_TYPE_REJECT,
	__XT_AUDIT_TYPE_MAX,
};

#define XT_AUDIT_TYPE_MAX (__XT_AUDIT_TYPE_MAX - 1)

struct xt_audit_info {
	__u8 type; /* XT_AUDIT_TYPE_* */
};

#endif /* _XT_AUDIT_TARGET_H */
