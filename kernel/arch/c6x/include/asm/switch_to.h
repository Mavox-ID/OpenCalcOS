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
#ifndef _ASM_C6X_SWITCH_TO_H
#define _ASM_C6X_SWITCH_TO_H

#include <beep/linkage.h>

#define prepare_to_switch()    do { } while (0)

struct task_struct;
struct thread_struct;
asmlinkage void *__switch_to(struct thread_struct *prev,
			     struct thread_struct *next,
			     struct task_struct *tsk);

#define switch_to(prev, next, last)				\
	do {							\
		current->thread.wchan = (u_long) __builtin_return_address(0); \
		(last) = __switch_to(&(prev)->thread,		\
				     &(next)->thread, (prev));	\
		mb();						\
		current->thread.wchan = 0;			\
	} while (0)

#endif /* _ASM_C6X_SWITCH_TO_H */
