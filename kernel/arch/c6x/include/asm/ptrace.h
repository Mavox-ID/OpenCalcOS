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
#ifndef _ASM_C6X_PTRACE_H
#define _ASM_C6X_PTRACE_H

#include <uapi/asm/ptrace.h>

#ifndef __ASSEMBLY__
#ifdef _BIG_ENDIAN
#else
#endif

#include <beep/linkage.h>

#define user_mode(regs)	((((regs)->tsr) & 0x40) != 0)

#define instruction_pointer(regs) ((regs)->pc)
#define profile_pc(regs) instruction_pointer(regs)
#define user_stack_pointer(regs) ((regs)->sp)

extern void show_regs(struct pt_regs *);

extern asmlinkage unsigned long syscall_trace_entry(struct pt_regs *regs);
extern asmlinkage void syscall_trace_exit(struct pt_regs *regs);

#endif /* __ASSEMBLY__ */
#endif /* _ASM_C6X_PTRACE_H */
