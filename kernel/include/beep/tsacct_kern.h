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
#ifndef _BEEP_TSACCT_KERN_H
#define _BEEP_TSACCT_KERN_H

#include <beep/taskstats.h>

#ifdef CONFIG_TASKSTATS
extern void bacct_add_tsk(struct user_namespace *user_ns,
			  struct pid_namespace *pid_ns,
			  struct taskstats *stats, struct task_struct *tsk);
#else
static inline void bacct_add_tsk(struct user_namespace *user_ns,
				 struct pid_namespace *pid_ns,
				 struct taskstats *stats, struct task_struct *tsk)
{}
#endif /* CONFIG_TASKSTATS */

#ifdef CONFIG_TASK_XACCT
extern void xacct_add_tsk(struct taskstats *stats, struct task_struct *p);
extern void acct_update_integrals(struct task_struct *tsk);
extern void acct_clear_integrals(struct task_struct *tsk);
#else
static inline void xacct_add_tsk(struct taskstats *stats, struct task_struct *p)
{}
static inline void acct_update_integrals(struct task_struct *tsk)
{}
static inline void acct_clear_integrals(struct task_struct *tsk)
{}
#endif /* CONFIG_TASK_XACCT */

#endif


