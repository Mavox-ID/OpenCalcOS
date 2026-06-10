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
#ifndef _ASM_TLBFLUSH_H
#define _ASM_TLBFLUSH_H

#include <beep/mm.h>
#include <asm/processor.h>

#ifdef CONFIG_MMU

#ifndef __ASSEMBLY__
extern void asmlinkage __flush_tlb_all(void);
extern void asmlinkage __flush_tlb_mm(unsigned long contextid);
extern void asmlinkage __flush_tlb_page(unsigned long contextid, unsigned long start);
extern void asmlinkage __flush_tlb_range(unsigned long contextid,
					 unsigned long start, unsigned long end);
#endif /* !__ASSEMBLY__ */

#define flush_tlb_all()				\
do {						\
	preempt_disable();			\
	__flush_tlb_all();			\
	preempt_enable();			\
} while(0)

#define flush_tlb_mm(mm)			\
do {						\
	preempt_disable();			\
	__flush_tlb_mm((mm)->context.id);	\
	preempt_enable();			\
} while(0)

#define flush_tlb_range(vma,start,end)					\
do {									\
	preempt_disable();						\
	__flush_tlb_range((vma)->vm_mm->context.id, start, end);	\
	preempt_enable();						\
} while(0)

#define flush_tlb_page(vma,addr)				\
do {								\
	preempt_disable();					\
	__flush_tlb_page((vma)->vm_mm->context.id, addr);	\
	preempt_enable();					\
} while(0)


#define __flush_tlb_global()			flush_tlb_all()
#define flush_tlb()				flush_tlb_all()
#define flush_tlb_kernel_range(start, end)	flush_tlb_all()

#else

#define flush_tlb()				BUG()
#define flush_tlb_all()				BUG()
#define flush_tlb_mm(mm)			BUG()
#define flush_tlb_page(vma,addr)		BUG()
#define flush_tlb_range(mm,start,end)		BUG()
#define flush_tlb_kernel_range(start, end)	BUG()

#endif


#endif /* _ASM_TLBFLUSH_H */
