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

#include <uapi/asm/ptrace.h>


#define user_mode(regs)			(((regs)->epsw & EPSW_nSL) == EPSW_nSL)
#define instruction_pointer(regs)	((regs)->pc)
#define user_stack_pointer(regs)	((regs)->sp)
#define current_pt_regs()		current_frame()

#define arch_has_single_step()	(1)

#define profile_pc(regs) ((regs)->pc)

#endif /* _ASM_PTRACE_H */
