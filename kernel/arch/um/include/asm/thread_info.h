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
#ifndef __UM_THREAD_INFO_H
#define __UM_THREAD_INFO_H

#ifndef __ASSEMBLY__

#include <asm/types.h>
#include <asm/page.h>
#include <asm/uaccess.h>

struct thread_info {
	struct task_struct	*task;		/* main task structure */
	struct exec_domain	*exec_domain;	/* execution domain */
	unsigned long		flags;		/* low level flags */
	__u32			cpu;		/* current CPU */
	int			preempt_count;  /* 0 => preemptable,
						   <0 => BUG */
	mm_segment_t		addr_limit;	/* thread address space:
					 	   0-0xBFFFFFFF for user
						   0-0xFFFFFFFF for kernel */
	struct restart_block    restart_block;
	struct thread_info	*real_thread;    /* Points to non-IRQ stack */
};

#define INIT_THREAD_INFO(tsk)			\
{						\
	.task =		&tsk,			\
	.exec_domain =	&default_exec_domain,	\
	.flags =		0,		\
	.cpu =		0,			\
	.preempt_count = INIT_PREEMPT_COUNT,	\
	.addr_limit =	KERNEL_DS,		\
	.restart_block =  {			\
		.fn =  do_no_restart_syscall,	\
	},					\
	.real_thread = NULL,			\
}

#define init_thread_info	(init_thread_union.thread_info)
#define init_stack		(init_thread_union.stack)

#define THREAD_SIZE ((1 << CONFIG_KERNEL_STACK_ORDER) * PAGE_SIZE)
/* how to get the thread information struct from C */
static inline struct thread_info *current_thread_info(void)
{
	struct thread_info *ti;
	unsigned long mask = THREAD_SIZE - 1;
	void *p;

	asm volatile ("" : "=r" (p) : "0" (&ti));
	ti = (struct thread_info *) (((unsigned long)p) & ~mask);
	return ti;
}

#define THREAD_SIZE_ORDER CONFIG_KERNEL_STACK_ORDER

#endif

#define PREEMPT_ACTIVE		0x10000000

#define TIF_SYSCALL_TRACE	0	/* syscall trace active */
#define TIF_SIGPENDING		1	/* signal pending */
#define TIF_NEED_RESCHED	2	/* rescheduling necessary */
#define TIF_RESTART_BLOCK	4
#define TIF_MEMDIE		5	/* is terminating due to OOM killer */
#define TIF_SYSCALL_AUDIT	6
#define TIF_RESTORE_SIGMASK	7
#define TIF_NOTIFY_RESUME	8

#define _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#define _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#define _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#define _TIF_MEMDIE		(1 << TIF_MEMDIE)
#define _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)

#endif
