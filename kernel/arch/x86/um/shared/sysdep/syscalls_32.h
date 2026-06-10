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
#include <asm/unistd.h>
#include <sysdep/ptrace.h>

typedef long syscall_handler_t(struct pt_regs);

/* Not declared on x86, incompatible declarations on x86_64, so these have
 * to go here rather than in sys_call_table.c
 */
extern syscall_handler_t sys_rt_sigaction;

extern syscall_handler_t *sys_call_table[];

#define EXECUTE_SYSCALL(syscall, regs) \
	((long (*)(struct syscall_args)) \
	 (*sys_call_table[syscall]))(SYSCALL_ARGS(&regs->regs))
