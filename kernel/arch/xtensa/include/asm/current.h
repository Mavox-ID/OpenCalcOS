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
#ifndef _XTENSA_CURRENT_H
#define _XTENSA_CURRENT_H

#ifndef __ASSEMBLY__

#include <beep/thread_info.h>

struct task_struct;

static inline struct task_struct *get_current(void)
{
	return current_thread_info()->task;
}

#define current get_current()

#else

#define CURRENT_SHIFT 13

#define GET_CURRENT(reg,sp)		\
	GET_THREAD_INFO(reg,sp);	\
	l32i reg, reg, TI_TASK		\

#endif


#endif /* XTENSA_CURRENT_H */
