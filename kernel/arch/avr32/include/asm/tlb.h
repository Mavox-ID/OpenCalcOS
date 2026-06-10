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
#ifndef __ASM_AVR32_TLB_H
#define __ASM_AVR32_TLB_H

#define tlb_start_vma(tlb, vma) \
	flush_cache_range(vma, vma->vm_start, vma->vm_end)

#define tlb_end_vma(tlb, vma) \
	flush_tlb_range(vma, vma->vm_start, vma->vm_end)

#define __tlb_remove_tlb_entry(tlb, pte, address) do { } while(0)

/*
 * Flush whole TLB for MM
 */
#define tlb_flush(tlb) flush_tlb_mm((tlb)->mm)

#include <asm-generic/tlb.h>

/*
 * For debugging purposes
 */
extern void show_dtlb_entry(unsigned int index);
extern void dump_dtlb(void);

#endif /* __ASM_AVR32_TLB_H */
