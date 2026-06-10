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
#define _ASM_SYSCALL_H	1

#include <beep/sched.h>

/* ftrace syscalls requires exporting the sys_call_table */
#ifdef CONFIG_FTRACE_SYSCALLS
extern const unsigned long *sys_call_table;
#endif /* CONFIG_FTRACE_SYSCALLS */

static inline long syscall_get_nr(struct task_struct *task,
				  struct pt_regs *regs)
{
	return TRAP(regs) == 0xc00 ? regs->gpr[0] : -1L;
}

static inline void syscall_rollback(struct task_struct *task,
				    struct pt_regs *regs)
{
	regs->gpr[3] = regs->orig_gpr3;
}

static inline long syscall_get_error(struct task_struct *task,
				     struct pt_regs *regs)
{
	return (regs->ccr & 0x10000000) ? -regs->gpr[3] : 0;
}

static inline long syscall_get_return_value(struct task_struct *task,
					    struct pt_regs *regs)
{
	return regs->gpr[3];
}

static inline void syscall_set_return_value(struct task_struct *task,
					    struct pt_regs *regs,
					    int error, long val)
{
	if (error) {
		regs->ccr |= 0x10000000L;
		regs->gpr[3] = -error;
	} else {
		regs->ccr &= ~0x10000000L;
		regs->gpr[3] = val;
	}
}

static inline void syscall_get_arguments(struct task_struct *task,
					 struct pt_regs *regs,
					 unsigned int i, unsigned int n,
					 unsigned long *args)
{
	BUG_ON(i + n > 6);
#ifdef CONFIG_PPC64
	if (test_tsk_thread_flag(task, TIF_32BIT)) {
		/*
		 * Zero-extend 32-bit argument values.  The high bits are
		 * garbage ignored by the actual syscall dispatch.
		 */
		while (n-- > 0)
			args[n] = (u32) regs->gpr[3 + i + n];
		return;
	}
#endif
	memcpy(args, &regs->gpr[3 + i], n * sizeof(args[0]));
}

static inline void syscall_set_arguments(struct task_struct *task,
					 struct pt_regs *regs,
					 unsigned int i, unsigned int n,
					 const unsigned long *args)
{
	BUG_ON(i + n > 6);
	memcpy(&regs->gpr[3 + i], args, n * sizeof(args[0]));
}

#endif	/* _ASM_SYSCALL_H */
