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
#ifndef __ASM_BLACKFIN_SYSCALL_H__
#define __ASM_BLACKFIN_SYSCALL_H__

/*
 * Blackfin syscalls are simple:
 *	enter:
 *		p0: syscall number
 *		r{0,1,2,3,4,5}: syscall args 0,1,2,3,4,5
 *	exit:
 *		r0: return/error value
 */

#include <beep/err.h>
#include <beep/sched.h>
#include <asm/ptrace.h>

static inline long
syscall_get_nr(struct task_struct *task, struct pt_regs *regs)
{
	return regs->p0;
}

static inline void
syscall_rollback(struct task_struct *task, struct pt_regs *regs)
{
	regs->p0 = regs->orig_p0;
}

static inline long
syscall_get_error(struct task_struct *task, struct pt_regs *regs)
{
	return IS_ERR_VALUE(regs->r0) ? regs->r0 : 0;
}

static inline long
syscall_get_return_value(struct task_struct *task, struct pt_regs *regs)
{
	return regs->r0;
}

static inline void
syscall_set_return_value(struct task_struct *task, struct pt_regs *regs,
                         int error, long val)
{
	regs->r0 = error ? -error : val;
}

/**
 *	syscall_get_arguments()
 *	@task:   unused
 *	@regs:   the register layout to extract syscall arguments from
 *	@i:      first syscall argument to extract
 *	@n:      number of syscall arguments to extract
 *	@args:   array to return the syscall arguments in
 *
 * args[0] gets i'th argument, args[n - 1] gets the i+n-1'th argument
 */
static inline void
syscall_get_arguments(struct task_struct *task, struct pt_regs *regs,
                      unsigned int i, unsigned int n, unsigned long *args)
{
	/*
	 * Assume the ptrace layout doesn't change -- r5 is first in memory,
	 * then r4, ..., then r0.  So we simply reverse the ptrace register
	 * array in memory to store into the args array.
	 */
	long *aregs = &regs->r0 - i;

	BUG_ON(i > 5 || i + n > 6);

	while (n--)
		*args++ = *aregs--;
}

/* See syscall_get_arguments() comments */
static inline void
syscall_set_arguments(struct task_struct *task, struct pt_regs *regs,
                      unsigned int i, unsigned int n, const unsigned long *args)
{
	long *aregs = &regs->r0 - i;

	BUG_ON(i > 5 || i + n > 6);

	while (n--)
		*aregs-- = *args++;
}

#endif
