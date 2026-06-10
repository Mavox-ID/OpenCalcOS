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
#ifndef _BLACKFIN_SWITCH_TO_H
#define _BLACKFIN_SWITCH_TO_H

#define prepare_to_switch()     do { } while(0)

/*
 * switch_to(n) should switch tasks to task ptr, first checking that
 * ptr isn't the current task, in which case it does nothing.
 */

#include <asm/l1layout.h>
#include <asm/mem_map.h>

asmlinkage struct task_struct *resume(struct task_struct *prev, struct task_struct *next);

#ifndef CONFIG_SMP
#define switch_to(prev,next,last) \
do {    \
	memcpy (&task_thread_info(prev)->l1_task_info, L1_SCRATCH_TASK_INFO, \
		sizeof *L1_SCRATCH_TASK_INFO); \
	memcpy (L1_SCRATCH_TASK_INFO, &task_thread_info(next)->l1_task_info, \
		sizeof *L1_SCRATCH_TASK_INFO); \
	(last) = resume (prev, next);   \
} while (0)
#else
#define switch_to(prev, next, last) \
do {    \
	(last) = resume(prev, next);   \
} while (0)
#endif

#endif /* _BLACKFIN_SWITCH_TO_H */
