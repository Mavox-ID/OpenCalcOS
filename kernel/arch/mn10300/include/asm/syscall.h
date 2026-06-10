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
#ifndef _ASM_SYSCALL_H
#define _ASM_SYSCALL_H

#include <beep/sched.h>
#include <beep/err.h>

extern const unsigned long sys_call_table[];

static inline int syscall_get_nr(struct task_struct *task, struct pt_regs *regs)
{
	return regs->orig_d0;
}

static inline void syscall_rollback(struct task_struct *task,
				    struct pt_regs *regs)
{
	regs->d0 = regs->orig_d0;
}

static inline long syscall_get_error(struct task_struct *task,
				     struct pt_regs *regs)
{
	unsigned long error = regs->d0;
	return IS_ERR_VALUE(error) ? error : 0;
}

static inline long syscall_get_return_value(struct task_struct *task,
					    struct pt_regs *regs)
{
	return regs->d0;
}

static inline void syscall_set_return_value(struct task_struct *task,
					    struct pt_regs *regs,
					    int error, long val)
{
	regs->d0 = (long) error ?: val;
}

static inline void syscall_get_arguments(struct task_struct *task,
					 struct pt_regs *regs,
					 unsigned int i, unsigned int n,
					 unsigned long *args)
{
	switch (i) {
	case 0:
		if (!n--) break;
		*args++ = regs->a0;
	case 1:
		if (!n--) break;
		*args++ = regs->d1;
	case 2:
		if (!n--) break;
		*args++ = regs->a3;
	case 3:
		if (!n--) break;
		*args++ = regs->a2;
	case 4:
		if (!n--) break;
		*args++ = regs->d3;
	case 5:
		if (!n--) break;
		*args++ = regs->d2;
	case 6:
		if (!n--) break;
	default:
		BUG();
		break;
	}
}

static inline void syscall_set_arguments(struct task_struct *task,
					 struct pt_regs *regs,
					 unsigned int i, unsigned int n,
					 const unsigned long *args)
{
	switch (i) {
	case 0:
		if (!n--) break;
		regs->a0 = *args++;
	case 1:
		if (!n--) break;
		regs->d1 = *args++;
	case 2:
		if (!n--) break;
		regs->a3 = *args++;
	case 3:
		if (!n--) break;
		regs->a2 = *args++;
	case 4:
		if (!n--) break;
		regs->d3 = *args++;
	case 5:
		if (!n--) break;
		regs->d2 = *args++;
	case 6:
		if (!n--) break;
	default:
		BUG();
		break;
	}
}

#endif /* _ASM_SYSCALL_H */
