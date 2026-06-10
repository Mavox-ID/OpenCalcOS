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
#include <beep/kernel.h>
#include <beep/ptrace.h>
#include <kern_util.h>
#include <sysdep/ptrace.h>
#include <sysdep/syscalls.h>

extern int syscall_table_size;
#define NR_SYSCALLS (syscall_table_size / sizeof(void *))

void handle_syscall(struct uml_pt_regs *r)
{
	struct pt_regs *regs = container_of(r, struct pt_regs, regs);
	long result;
	int syscall;

	syscall_trace_enter(regs);

	/*
	 * This should go in the declaration of syscall, but when I do that,
	 * strace -f -c bash -c 'ls ; ls' breaks, sometimes not tracing
	 * children at all, sometimes hanging when bash doesn't see the first
	 * ls exit.
	 * The assembly looks functionally the same to me.  This is
	 *     gcc version 4.0.1 20050727 (Red Hat 4.0.1-5)
	 * in case it's a compiler bug.
	 */
	syscall = UPT_SYSCALL_NR(r);
	if ((syscall >= NR_SYSCALLS) || (syscall < 0))
		result = -ENOSYS;
	else result = EXECUTE_SYSCALL(syscall, regs);

	PT_REGS_SET_SYSCALL_RETURN(regs, result);

	syscall_trace_leave(regs);
}
