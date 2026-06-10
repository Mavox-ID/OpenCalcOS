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
#ifndef __ASM_SPARC_PROCESSOR_H
#define __ASM_SPARC_PROCESSOR_H

/*
 * Sparc32 implementation of macro that returns current
 * instruction pointer ("program counter").
 */
#define current_text_addr() ({ void *pc; __asm__("sethi %%hi(1f), %0; or %0, %%lo(1f), %0;\n1:" : "=r" (pc)); pc; })

#include <asm/psr.h>
#include <asm/ptrace.h>
#include <asm/head.h>
#include <asm/signal.h>
#include <asm/page.h>

/*
 * The sparc has no problems with write protection
 */
#define wp_works_ok 1
#define wp_works_ok__is_a_macro /* for versions in ksyms.c */

/* Whee, this is STACK_TOP + PAGE_SIZE and the lowest kernel address too...
 * That one page is used to protect kernel from intruders, so that
 * we can make our access_ok test faster
 */
#define TASK_SIZE	PAGE_OFFSET
#ifdef __KERNEL__
#define STACK_TOP	(PAGE_OFFSET - PAGE_SIZE)
#define STACK_TOP_MAX	STACK_TOP
#endif /* __KERNEL__ */

struct task_struct;

#ifdef __KERNEL__
struct fpq {
	unsigned long *insn_addr;
	unsigned long insn;
};
#endif

typedef struct {
	int seg;
} mm_segment_t;

/* The Sparc processor specific thread struct. */
struct thread_struct {
	struct pt_regs *kregs;
	unsigned int _pad1;

	/* Special child fork kpsr/kwim values. */
	unsigned long fork_kpsr __attribute__ ((aligned (8)));
	unsigned long fork_kwim;

	/* Floating point regs */
	unsigned long   float_regs[32] __attribute__ ((aligned (8)));
	unsigned long   fsr;
	unsigned long   fpqdepth;
	struct fpq	fpqueue[16];
	unsigned long flags;
	mm_segment_t current_ds;
};

#define SPARC_FLAG_KTHREAD      0x1    /* task is a kernel thread */
#define SPARC_FLAG_UNALIGNED    0x2    /* is allowed to do unaligned accesses */

#define INIT_THREAD  { \
	.flags = SPARC_FLAG_KTHREAD, \
	.current_ds = KERNEL_DS, \
}

/* Return saved PC of a blocked thread. */
extern unsigned long thread_saved_pc(struct task_struct *t);

/* Do necessary setup to start up a newly executed thread. */
static inline void start_thread(struct pt_regs * regs, unsigned long pc,
				    unsigned long sp)
{
	register unsigned long zero asm("g1");

	regs->psr = (regs->psr & (PSR_CWP)) | PSR_S;
	regs->pc = ((pc & (~3)) - 4);
	regs->npc = regs->pc + 4;
	regs->y = 0;
	zero = 0;
	__asm__ __volatile__("std\t%%g0, [%0 + %3 + 0x00]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x08]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x10]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x18]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x20]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x28]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x30]\n\t"
			     "st\t%1, [%0 + %3 + 0x38]\n\t"
			     "st\t%%g0, [%0 + %3 + 0x3c]"
			     : /* no outputs */
			     : "r" (regs),
			       "r" (sp - sizeof(struct reg_window32)),
			       "r" (zero),
			       "i" ((const unsigned long)(&((struct pt_regs *)0)->u_regs[0]))
			     : "memory");
}

/* Free all resources held by a thread. */
#define release_thread(tsk)		do { } while(0)

extern unsigned long get_wchan(struct task_struct *);

#define task_pt_regs(tsk) ((tsk)->thread.kregs)
#define KSTK_EIP(tsk)  ((tsk)->thread.kregs->pc)
#define KSTK_ESP(tsk)  ((tsk)->thread.kregs->u_regs[UREG_FP])

#ifdef __KERNEL__

extern struct task_struct *last_task_used_math;

#define cpu_relax()	barrier()

#endif

#endif /* __ASM_SPARC_PROCESSOR_H */
