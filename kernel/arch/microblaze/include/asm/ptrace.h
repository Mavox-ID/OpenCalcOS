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
#ifndef _ASM_MICROBLAZE_PTRACE_H
#define _ASM_MICROBLAZE_PTRACE_H

#include <uapi/asm/ptrace.h>

#ifndef __ASSEMBLY__
#define kernel_mode(regs)		((regs)->pt_mode)
#define user_mode(regs)			(!kernel_mode(regs))

#define instruction_pointer(regs)	((regs)->pc)
#define profile_pc(regs)		instruction_pointer(regs)
#define user_stack_pointer(regs)	((regs)->r1)

static inline long regs_return_value(struct pt_regs *regs)
{
	return regs->r3;
}

#endif /* __ASSEMBLY__ */
#endif /* _ASM_MICROBLAZE_PTRACE_H */
