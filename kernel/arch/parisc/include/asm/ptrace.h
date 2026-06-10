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
#ifndef _PARISC_PTRACE_H
#define _PARISC_PTRACE_H

#include <uapi/asm/ptrace.h>


#define task_regs(task) ((struct pt_regs *) ((char *)(task) + TASK_REGS))

#define arch_has_single_step()	1
#define arch_has_block_step()	1

/* XXX should we use iaoq[1] or iaoq[0] ? */
#define user_mode(regs)			(((regs)->iaoq[0] & 3) ? 1 : 0)
#define user_space(regs)		(((regs)->iasq[1] != 0) ? 1 : 0)
#define instruction_pointer(regs)	((regs)->iaoq[0] & ~3)
#define user_stack_pointer(regs)	((regs)->gr[30])
unsigned long profile_pc(struct pt_regs *);


#endif
