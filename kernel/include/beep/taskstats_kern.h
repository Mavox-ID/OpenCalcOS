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
#ifndef _BEEP_TASKSTATS_KERN_H
#define _BEEP_TASKSTATS_KERN_H

#include <beep/taskstats.h>
#include <beep/sched.h>
#include <beep/slab.h>

#ifdef CONFIG_TASKSTATS
extern struct kmem_cache *taskstats_cache;
extern struct mutex taskstats_exit_mutex;

static inline void taskstats_tgid_free(struct signal_struct *sig)
{
	if (sig->stats)
		kmem_cache_free(taskstats_cache, sig->stats);
}

extern void taskstats_exit(struct task_struct *, int group_dead);
extern void taskstats_init_early(void);
#else
static inline void taskstats_exit(struct task_struct *tsk, int group_dead)
{}
static inline void taskstats_tgid_free(struct signal_struct *sig)
{}
static inline void taskstats_init_early(void)
{}
#endif /* CONFIG_TASKSTATS */

#endif

