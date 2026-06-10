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
#include <beep/signal.h>
#include <beep/rwsem.h>
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/string.h>
#include <beep/types.h>
#include <beep/ptrace.h>
#include <beep/mman.h>
#include <beep/mm.h>
#include <beep/smp.h>
#include <beep/perf_event.h>
#include <beep/interrupt.h>
#include <asm/io.h>
#include <asm/tlb.h>
#include <asm/uaccess.h>
#include <asm/pgalloc.h>
#include <asm/mmu_context.h>

void local_flush_tlb_one(unsigned long asid, unsigned long page)
{
	unsigned long long match, pteh=0, lpage;
	unsigned long tlb;

	/*
	 * Sign-extend based on neff.
	 */
	lpage = neff_sign_extend(page);
	match = (asid << PTEH_ASID_SHIFT) | PTEH_VALID;
	match |= lpage;

	for_each_itlb_entry(tlb) {
		asm volatile ("getcfg	%1, 0, %0"
			      : "=r" (pteh)
			      : "r" (tlb) );

		if (pteh == match) {
			__flush_tlb_slot(tlb);
			break;
		}
	}

	for_each_dtlb_entry(tlb) {
		asm volatile ("getcfg	%1, 0, %0"
			      : "=r" (pteh)
			      : "r" (tlb) );

		if (pteh == match) {
			__flush_tlb_slot(tlb);
			break;
		}

	}
}

void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long page)
{
	unsigned long flags;

	if (vma->vm_mm) {
		page &= PAGE_MASK;
		local_irq_save(flags);
		local_flush_tlb_one(get_asid(), page);
		local_irq_restore(flags);
	}
}

void local_flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
			   unsigned long end)
{
	unsigned long flags;
	unsigned long long match, pteh=0, pteh_epn, pteh_low;
	unsigned long tlb;
	unsigned int cpu = smp_processor_id();
	struct mm_struct *mm;

	mm = vma->vm_mm;
	if (cpu_context(cpu, mm) == NO_CONTEXT)
		return;

	local_irq_save(flags);

	start &= PAGE_MASK;
	end &= PAGE_MASK;

	match = (cpu_asid(cpu, mm) << PTEH_ASID_SHIFT) | PTEH_VALID;

	/* Flush ITLB */
	for_each_itlb_entry(tlb) {
		asm volatile ("getcfg	%1, 0, %0"
			      : "=r" (pteh)
			      : "r" (tlb) );

		pteh_epn = pteh & PAGE_MASK;
		pteh_low = pteh & ~PAGE_MASK;

		if (pteh_low == match && pteh_epn >= start && pteh_epn <= end)
			__flush_tlb_slot(tlb);
	}

	/* Flush DTLB */
	for_each_dtlb_entry(tlb) {
		asm volatile ("getcfg	%1, 0, %0"
			      : "=r" (pteh)
			      : "r" (tlb) );

		pteh_epn = pteh & PAGE_MASK;
		pteh_low = pteh & ~PAGE_MASK;

		if (pteh_low == match && pteh_epn >= start && pteh_epn <= end)
			__flush_tlb_slot(tlb);
	}

	local_irq_restore(flags);
}

void local_flush_tlb_mm(struct mm_struct *mm)
{
	unsigned long flags;
	unsigned int cpu = smp_processor_id();

	if (cpu_context(cpu, mm) == NO_CONTEXT)
		return;

	local_irq_save(flags);

	cpu_context(cpu, mm) = NO_CONTEXT;
	if (mm == current->mm)
		activate_context(mm, cpu);

	local_irq_restore(flags);
}

void local_flush_tlb_all(void)
{
	/* Invalidate all, including shared pages, excluding fixed TLBs */
	unsigned long flags, tlb;

	local_irq_save(flags);

	/* Flush each ITLB entry */
	for_each_itlb_entry(tlb)
		__flush_tlb_slot(tlb);

	/* Flush each DTLB entry */
	for_each_dtlb_entry(tlb)
		__flush_tlb_slot(tlb);

	local_irq_restore(flags);
}

void local_flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
        /* FIXME: Optimize this later.. */
        flush_tlb_all();
}

void __flush_tlb_global(void)
{
	flush_tlb_all();
}
