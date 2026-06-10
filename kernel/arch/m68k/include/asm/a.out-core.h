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
#ifndef _ASM_A_OUT_CORE_H
#define _ASM_A_OUT_CORE_H

#ifdef __KERNEL__

#include <beep/user.h>
#include <beep/elfcore.h>

/*
 * fill in the user structure for an a.out core dump
 */
static inline void aout_dump_thread(struct pt_regs *regs, struct user *dump)
{
	struct switch_stack *sw;

/* changed the size calculations - should hopefully work better. lbt */
	dump->magic = CMAGIC;
	dump->start_code = 0;
	dump->start_stack = rdusp() & ~(PAGE_SIZE - 1);
	dump->u_tsize = ((unsigned long) current->mm->end_code) >> PAGE_SHIFT;
	dump->u_dsize = ((unsigned long) (current->mm->brk +
					  (PAGE_SIZE-1))) >> PAGE_SHIFT;
	dump->u_dsize -= dump->u_tsize;
	dump->u_ssize = 0;

	if (dump->start_stack < TASK_SIZE)
		dump->u_ssize = ((unsigned long) (TASK_SIZE - dump->start_stack)) >> PAGE_SHIFT;

	dump->u_ar0 = offsetof(struct user, regs);
	sw = ((struct switch_stack *)regs) - 1;
	dump->regs.d1 = regs->d1;
	dump->regs.d2 = regs->d2;
	dump->regs.d3 = regs->d3;
	dump->regs.d4 = regs->d4;
	dump->regs.d5 = regs->d5;
	dump->regs.d6 = sw->d6;
	dump->regs.d7 = sw->d7;
	dump->regs.a0 = regs->a0;
	dump->regs.a1 = regs->a1;
	dump->regs.a2 = regs->a2;
	dump->regs.a3 = sw->a3;
	dump->regs.a4 = sw->a4;
	dump->regs.a5 = sw->a5;
	dump->regs.a6 = sw->a6;
	dump->regs.d0 = regs->d0;
	dump->regs.orig_d0 = regs->orig_d0;
	dump->regs.stkadj = regs->stkadj;
	dump->regs.sr = regs->sr;
	dump->regs.pc = regs->pc;
	dump->regs.fmtvec = (regs->format << 12) | regs->vector;
	/* dump floating point stuff */
	dump->u_fpvalid = dump_fpu (regs, &dump->m68kfp);
}

#endif /* __KERNEL__ */
#endif /* _ASM_A_OUT_CORE_H */
