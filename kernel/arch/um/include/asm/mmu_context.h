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
#ifndef __UM_MMU_CONTEXT_H
#define __UM_MMU_CONTEXT_H

#include <beep/sched.h>
#include <asm/mmu.h>

extern void uml_setup_stubs(struct mm_struct *mm);
extern void arch_exit_mmap(struct mm_struct *mm);

#define deactivate_mm(tsk,mm)	do { } while (0)

extern void force_flush_all(void);

static inline void activate_mm(struct mm_struct *old, struct mm_struct *new)
{
	/*
	 * This is called by fs/exec.c and sys_unshare()
	 * when the new ->mm is used for the first time.
	 */
	__switch_mm(&new->context.id);
	down_write(&new->mmap_sem);
	uml_setup_stubs(new);
	up_write(&new->mmap_sem);
}

static inline void switch_mm(struct mm_struct *prev, struct mm_struct *next, 
			     struct task_struct *tsk)
{
	unsigned cpu = smp_processor_id();

	if(prev != next){
		cpumask_clear_cpu(cpu, mm_cpumask(prev));
		cpumask_set_cpu(cpu, mm_cpumask(next));
		if(next != &init_mm)
			__switch_mm(&next->context.id);
	}
}

static inline void arch_dup_mmap(struct mm_struct *oldmm, struct mm_struct *mm)
{
	uml_setup_stubs(mm);
}

static inline void enter_lazy_tlb(struct mm_struct *mm, 
				  struct task_struct *tsk)
{
}

extern int init_new_context(struct task_struct *task, struct mm_struct *mm);

extern void destroy_context(struct mm_struct *mm);

#endif
