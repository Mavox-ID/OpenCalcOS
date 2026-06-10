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
#ifndef __UM_PTRACE_GENERIC_H
#define __UM_PTRACE_GENERIC_H

#ifndef __ASSEMBLY__

#include <asm/ptrace-abi.h>
#include <sysdep/ptrace.h>

struct pt_regs {
	struct uml_pt_regs regs;
};

#define arch_has_single_step()	(1)

#define EMPTY_REGS { .regs = EMPTY_UML_PT_REGS }

#define PT_REGS_IP(r) UPT_IP(&(r)->regs)
#define PT_REGS_SP(r) UPT_SP(&(r)->regs)

#define PT_REGS_RESTART_SYSCALL(r) UPT_RESTART_SYSCALL(&(r)->regs)

#define PT_REGS_SYSCALL_NR(r) UPT_SYSCALL_NR(&(r)->regs)

#define instruction_pointer(regs) PT_REGS_IP(regs)

struct task_struct;

extern long subarch_ptrace(struct task_struct *child, long request,
	unsigned long addr, unsigned long data);
extern unsigned long getreg(struct task_struct *child, int regno);
extern int putreg(struct task_struct *child, int regno, unsigned long value);

extern int arch_copy_tls(struct task_struct *new);
extern void clear_flushed_tls(struct task_struct *task);
extern void syscall_trace_enter(struct pt_regs *regs);
extern void syscall_trace_leave(struct pt_regs *regs);

#endif

#endif
