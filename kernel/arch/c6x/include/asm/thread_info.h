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
#ifndef _ASM_C6X_THREAD_INFO_H
#define _ASM_C6X_THREAD_INFO_H

#ifdef __KERNEL__

#include <asm/page.h>

#ifdef CONFIG_4KSTACKS
#define THREAD_SIZE		4096
#define THREAD_SHIFT		12
#define THREAD_SIZE_ORDER	0
#else
#define THREAD_SIZE		8192
#define THREAD_SHIFT		13
#define THREAD_SIZE_ORDER	1
#endif

#define THREAD_START_SP		(THREAD_SIZE - 8)

#ifndef __ASSEMBLY__

typedef struct {
	unsigned long seg;
} mm_segment_t;

/*
 * low level task data.
 */
struct thread_info {
	struct task_struct	*task;		/* main task structure */
	struct exec_domain	*exec_domain;	/* execution domain */
	unsigned long		flags;		/* low level flags */
	int			cpu;		/* cpu we're on */
	int			preempt_count;	/* 0 = preemptable, <0 = BUG */
	mm_segment_t		addr_limit;	/* thread address space */
	struct restart_block	restart_block;
};

/*
 * macros/functions for gaining access to the thread information structure
 *
 * preempt_count needs to be 1 initially, until the scheduler is functional.
 */
#define INIT_THREAD_INFO(tsk)			\
{						\
	.task		= &tsk,			\
	.exec_domain	= &default_exec_domain,	\
	.flags		= 0,			\
	.cpu		= 0,			\
	.preempt_count	= INIT_PREEMPT_COUNT,	\
	.addr_limit	= KERNEL_DS,		\
	.restart_block	= {			\
		.fn = do_no_restart_syscall,	\
	},					\
}

#define init_thread_info	(init_thread_union.thread_info)
#define init_stack		(init_thread_union.stack)

/* get the thread information struct of current task */
static inline __attribute__((const))
struct thread_info *current_thread_info(void)
{
	struct thread_info *ti;
	asm volatile (" clr   .s2 B15,0,%1,%0\n"
		      : "=b" (ti)
		      : "Iu5" (THREAD_SHIFT - 1));
	return ti;
}

#define get_thread_info(ti)	get_task_struct((ti)->task)
#define put_thread_info(ti)	put_task_struct((ti)->task)
#endif /* __ASSEMBLY__ */

#define	PREEMPT_ACTIVE	0x10000000

/*
 * thread information flag bit numbers
 * - pending work-to-be-done flags are in LSW
 * - other flags in MSW
 */
#define TIF_SYSCALL_TRACE	0	/* syscall trace active */
#define TIF_NOTIFY_RESUME	1	/* resumption notification requested */
#define TIF_SIGPENDING		2	/* signal pending */
#define TIF_NEED_RESCHED	3	/* rescheduling necessary */
#define TIF_RESTORE_SIGMASK	4	/* restore signal mask in do_signal() */

#define TIF_MEMDIE		17	/* OOM killer killed process */

#define TIF_WORK_MASK		0x00007FFE /* work on irq/exception return */
#define TIF_ALLWORK_MASK	0x00007FFF /* work on any return to u-space */

#endif /* __KERNEL__ */

#endif /* _ASM_C6X_THREAD_INFO_H */
