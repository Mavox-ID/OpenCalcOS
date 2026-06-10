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
#ifndef _ASM_MICROBLAZE_PROCESSOR_H
#define _ASM_MICROBLAZE_PROCESSOR_H

#include <asm/ptrace.h>
#include <asm/setup.h>
#include <asm/registers.h>
#include <asm/entry.h>
#include <asm/current.h>

# ifndef __ASSEMBLY__
/* from kernel/cpu/mb.c */
extern const struct seq_operations cpuinfo_op;

# define cpu_relax()		barrier()
# define cpu_sleep()		do {} while (0)

#define task_pt_regs(tsk) \
		(((struct pt_regs *)(THREAD_SIZE + task_stack_page(tsk))) - 1)

/* Do necessary setup to start up a newly executed thread. */
void start_thread(struct pt_regs *regs, unsigned long pc, unsigned long usp);

extern void ret_from_fork(void);
extern void ret_from_kernel_thread(void);

# endif /* __ASSEMBLY__ */

# ifndef CONFIG_MMU
/*
 * User space process size: memory size
 *
 * TASK_SIZE on MMU cpu is usually 1GB. However, on no-MMU arch, both
 * user processes and the kernel is on the same memory region. They
 * both share the memory space and that is limited by the amount of
 * physical memory. thus, we set TASK_SIZE == amount of total memory.
 */
# define TASK_SIZE	(0x81000000 - 0x80000000)

/*
 * Default implementation of macro that returns current
 * instruction pointer ("program counter").
 */
# define current_text_addr() ({ __label__ _l; _l: &&_l; })

/*
 * This decides where the kernel will search for a free chunk of vm
 * space during mmap's. We won't be using it
 */
# define TASK_UNMAPPED_BASE	0

/* definition in include/beep/sched.h */
struct task_struct;

/* thread_struct is gone. use thread_info instead. */
struct thread_struct { };
# define INIT_THREAD	{ }

/* Free all resources held by a thread. */
static inline void release_thread(struct task_struct *dead_task)
{
}

/* Free all resources held by a thread. */
static inline void exit_thread(void)
{
}

extern unsigned long thread_saved_pc(struct task_struct *t);

extern unsigned long get_wchan(struct task_struct *p);

# define KSTK_EIP(tsk)	(0)
# define KSTK_ESP(tsk)	(0)

# else /* CONFIG_MMU */

/*
 * This is used to define STACK_TOP, and with MMU it must be below
 * kernel base to select the correct PGD when handling MMU exceptions.
 */
# define TASK_SIZE	(CONFIG_KERNEL_START)

/*
 * This decides where the kernel will search for a free chunk of vm
 * space during mmap's.
 */
# define TASK_UNMAPPED_BASE	(TASK_SIZE / 8 * 3)

# define THREAD_KSP	0

#  ifndef __ASSEMBLY__

/*
 * Default implementation of macro that returns current
 * instruction pointer ("program counter").
 */
#  define current_text_addr()	({ __label__ _l; _l: &&_l; })

/* If you change this, you must change the associated assembly-languages
 * constants defined below, THREAD_*.
 */
struct thread_struct {
	/* kernel stack pointer (must be first field in structure) */
	unsigned long	ksp;
	unsigned long	ksp_limit;	/* if ksp <= ksp_limit stack overflow */
	void		*pgdir;		/* root of page-table tree */
	struct pt_regs	*regs;		/* Pointer to saved register state */
};

#  define INIT_THREAD { \
	.ksp   = sizeof init_stack + (unsigned long)init_stack, \
	.pgdir = swapper_pg_dir, \
}

/* Free all resources held by a thread. */
extern inline void release_thread(struct task_struct *dead_task)
{
}

/* Free current thread data structures etc.  */
static inline void exit_thread(void)
{
}

/* Return saved (kernel) PC of a blocked thread.  */
#  define thread_saved_pc(tsk)	\
	((tsk)->thread.regs ? (tsk)->thread.regs->r15 : 0)

unsigned long get_wchan(struct task_struct *p);

/* The size allocated for kernel stacks. This _must_ be a power of two! */
# define KERNEL_STACK_SIZE	0x2000

/* Return some info about the user process TASK.  */
#  define task_tos(task)	((unsigned long)(task) + KERNEL_STACK_SIZE)
#  define task_regs(task) ((struct pt_regs *)task_tos(task) - 1)

#  define task_pt_regs_plus_args(tsk) \
	((void *)task_pt_regs(tsk))

#  define task_sp(task)	(task_regs(task)->r1)
#  define task_pc(task)	(task_regs(task)->pc)
/* Grotty old names for some.  */
#  define KSTK_EIP(task)	(task_pc(task))
#  define KSTK_ESP(task)	(task_sp(task))

/* FIXME */
#  define deactivate_mm(tsk, mm)	do { } while (0)

#  define STACK_TOP	TASK_SIZE
#  define STACK_TOP_MAX	STACK_TOP

void disable_hlt(void);
void enable_hlt(void);
void default_idle(void);

#ifdef CONFIG_DEBUG_FS
extern struct dentry *of_debugfs_root;
#endif

#  endif /* __ASSEMBLY__ */
# endif /* CONFIG_MMU */
#endif /* _ASM_MICROBLAZE_PROCESSOR_H */
