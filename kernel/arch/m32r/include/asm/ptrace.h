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
#ifndef _ASM_M32R_PTRACE_H
#define _ASM_M32R_PTRACE_H


#include <asm/m32r.h>		/* M32R_PSW_BSM, M32R_PSW_BPM */
#include <uapi/asm/ptrace.h>

#define arch_has_single_step() (1)

struct task_struct;
extern void init_debug_traps(struct task_struct *);
#define arch_ptrace_attach(child) \
	init_debug_traps(child)

#if defined(CONFIG_ISA_M32R2) || defined(CONFIG_CHIP_VDEC2)
#define user_mode(regs) ((M32R_PSW_BPM & (regs)->psw) != 0)
#elif defined(CONFIG_ISA_M32R)
#define user_mode(regs) ((M32R_PSW_BSM & (regs)->psw) != 0)
#else
#error unknown isa configuration
#endif

#define instruction_pointer(regs) ((regs)->bpc)
#define profile_pc(regs) instruction_pointer(regs)
#define user_stack_pointer(regs) ((regs)->spu)

extern void withdraw_debug_trap(struct pt_regs *regs);

#define task_pt_regs(task) \
        ((struct pt_regs *)(task_stack_page(task) + THREAD_SIZE) - 1)
#define current_pt_regs() ((struct pt_regs *) \
	((unsigned long)current_thread_info() + THREAD_SIZE) - 1)

#endif /* _ASM_M32R_PTRACE_H */
