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
#ifndef _BFIN_PTRACE_H
#define _BFIN_PTRACE_H

#include <uapi/asm/ptrace.h>

#ifndef __ASSEMBLY__

/* user_mode returns true if only one bit is set in IPEND, other than the
   master interrupt enable.  */
#define user_mode(regs) (!(((regs)->ipend & ~0x10) & (((regs)->ipend & ~0x10) - 1)))

#define arch_has_single_step()	(1)
/* common code demands this function */
#define ptrace_disable(child) user_disable_single_step(child)
#define current_user_stack_pointer() rdusp()

extern int is_user_addr_valid(struct task_struct *child,
			      unsigned long start, unsigned long len);

/*
 * Get the address of the live pt_regs for the specified task.
 * These are saved onto the top kernel stack when the process
 * is not running.
 *
 * Note: if a user thread is execve'd from kernel space, the
 * kernel stack will not be empty on entry to the kernel, so
 * ptracing these tasks will fail.
 */
#define task_pt_regs(task) \
	(struct pt_regs *) \
	    ((unsigned long)task_stack_page(task) + \
	     (THREAD_SIZE - sizeof(struct pt_regs)))

#include <asm-generic/ptrace.h>

#endif				/* __ASSEMBLY__ */
#endif				/* _BFIN_PTRACE_H */
