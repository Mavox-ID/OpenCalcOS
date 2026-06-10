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

/*
 * TLB flushing -- in "SMP", these routines get defined to be the
 * ones from smp.c, else they are some local flavors.
 */

/*
 * These functions are commonly macros, but in the interests of
 * VM vs. native implementation and code size, we simply declare
 * the function prototypes here.
 */
extern void tlb_flush_all(void);
extern void flush_tlb_mm(struct mm_struct *mm);
extern void flush_tlb_page(struct vm_area_struct *vma, unsigned long addr);
extern void flush_tlb_range(struct vm_area_struct *vma,
				unsigned long start, unsigned long end);
extern void flush_tlb_kernel_range(unsigned long start, unsigned long end);
extern void flush_tlb_one(unsigned long);

/*
 * "This is called in munmap when we have freed up some page-table pages.
 * We don't need to do anything here..."
 *
 * The VM kernel doesn't walk page tables, and they are passed to the VMM
 * by logical address. There doesn't seem to be any possibility that they
 * could be referenced by the VM kernel based on a stale mapping, since
 * they would only be located by consulting the mm structure, and they
 * will have been purged from that structure by the munmap.  Seems like
 * a noop on HVM as well.
 */
#define flush_tlb_pgtables(mm, start, end)

#endif
