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
#ifndef _ASM_PTRACE_H
#define _ASM_PTRACE_H

#include <asm/registers.h>

#define instruction_pointer(regs) pt_elr(regs)
#define user_stack_pointer(regs) ((regs)->r29)

#define profile_pc(regs) instruction_pointer(regs)

/* kprobe-based event tracer support */
extern int regs_query_register_offset(const char *name);
extern const char *regs_query_register_name(unsigned int offset);

#define current_pt_regs() \
	((struct pt_regs *) \
	 ((unsigned long)current_thread_info() + THREAD_SIZE) - 1)

#endif
