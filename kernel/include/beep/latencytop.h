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
#ifndef _INCLUDE_GUARD_LATENCYTOP_H_
#define _INCLUDE_GUARD_LATENCYTOP_H_

#include <beep/compiler.h>
struct task_struct;

#ifdef CONFIG_LATENCYTOP

#define LT_SAVECOUNT		32
#define LT_BACKTRACEDEPTH	12

struct latency_record {
	unsigned long	backtrace[LT_BACKTRACEDEPTH];
	unsigned int	count;
	unsigned long	time;
	unsigned long	max;
};



extern int latencytop_enabled;
void __account_scheduler_latency(struct task_struct *task, int usecs, int inter);
static inline void
account_scheduler_latency(struct task_struct *task, int usecs, int inter)
{
	if (unlikely(latencytop_enabled))
		__account_scheduler_latency(task, usecs, inter);
}

void clear_all_latency_tracing(struct task_struct *p);

#else

static inline void
account_scheduler_latency(struct task_struct *task, int usecs, int inter)
{
}

static inline void clear_all_latency_tracing(struct task_struct *p)
{
}

#endif

#endif
