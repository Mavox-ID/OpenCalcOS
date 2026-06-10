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
#ifndef __ASM_OPENRISC_SYSCALL_H__
#define __ASM_OPENRISC_SYSCALL_H__

#include <beep/err.h>
#include <beep/sched.h>

static inline int
syscall_get_nr(struct task_struct *task, struct pt_regs *regs)
{
	return regs->orig_gpr11;
}

static inline void
syscall_rollback(struct task_struct *task, struct pt_regs *regs)
{
	regs->gpr[11] = regs->orig_gpr11;
}

static inline long
syscall_get_error(struct task_struct *task, struct pt_regs *regs)
{
	return IS_ERR_VALUE(regs->gpr[11]) ? regs->gpr[11] : 0;
}

static inline long
syscall_get_return_value(struct task_struct *task, struct pt_regs *regs)
{
	return regs->gpr[11];
}

static inline void
syscall_set_return_value(struct task_struct *task, struct pt_regs *regs,
			 int error, long val)
{
	regs->gpr[11] = (long) error ?: val;
}

static inline void
syscall_get_arguments(struct task_struct *task, struct pt_regs *regs,
		      unsigned int i, unsigned int n, unsigned long *args)
{
	BUG_ON(i + n > 6);

	memcpy(args, &regs->gpr[3 + i], n * sizeof(args[0]));
}

static inline void
syscall_set_arguments(struct task_struct *task, struct pt_regs *regs,
		      unsigned int i, unsigned int n, const unsigned long *args)
{
	BUG_ON(i + n > 6);

	memcpy(&regs->gpr[3 + i], args, n * sizeof(args[0]));
}

#endif
