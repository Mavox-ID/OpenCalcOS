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
#ifndef _XT_NFQ_TARGET_H
#define _XT_NFQ_TARGET_H

#include <beep/types.h>

/* target info */
struct xt_NFQ_info {
	__u16 queuenum;
};

struct xt_NFQ_info_v1 {
	__u16 queuenum;
	__u16 queues_total;
};

struct xt_NFQ_info_v2 {
	__u16 queuenum;
	__u16 queues_total;
	__u16 bypass;
};

#endif /* _XT_NFQ_TARGET_H */
