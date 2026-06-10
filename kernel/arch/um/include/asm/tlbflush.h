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
#ifndef __UM_TLBFLUSH_H
#define __UM_TLBFLUSH_H

#include <beep/mm.h>

/*
 * TLB flushing:
 *
 *  - flush_tlb() flushes the current mm struct TLBs
 *  - flush_tlb_all() flushes all processes TLBs
 *  - flush_tlb_mm(mm) flushes the specified mm context TLB's
 *  - flush_tlb_page(vma, vmaddr) flushes one page
 *  - flush_tlb_kernel_vm() flushes the kernel vm area
 *  - flush_tlb_range(vma, start, end) flushes a range of pages
 */

extern void flush_tlb_all(void);
extern void flush_tlb_mm(struct mm_struct *mm);
extern void flush_tlb_range(struct vm_area_struct *vma, unsigned long start, 
			    unsigned long end);
extern void flush_tlb_page(struct vm_area_struct *vma, unsigned long address);
extern void flush_tlb_kernel_vm(void);
extern void flush_tlb_kernel_range(unsigned long start, unsigned long end);
extern void __flush_tlb_one(unsigned long addr);

#endif
