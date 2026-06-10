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
#ifndef _XT_IDLETIMER_H
#define _XT_IDLETIMER_H

#include <beep/types.h>

#define MAX_IDLETIMER_LABEL_SIZE 28

struct idletimer_tg_info {
	__u32 timeout;

	char label[MAX_IDLETIMER_LABEL_SIZE];

	/* for kernel module internal use only */
	struct idletimer_tg *timer __attribute__((aligned(8)));
};

#endif
