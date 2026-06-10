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
#ifndef __UNICORE_TLB_H__
#define __UNICORE_TLB_H__

#define tlb_start_vma(tlb, vma)				do { } while (0)
#define tlb_end_vma(tlb, vma)				do { } while (0)
#define __tlb_remove_tlb_entry(tlb, ptep, address)	do { } while (0)
#define tlb_flush(tlb) flush_tlb_mm((tlb)->mm)

#define __pte_free_tlb(tlb, pte, addr)				\
	do {							\
		pgtable_page_dtor(pte);				\
		tlb_remove_page((tlb), (pte));			\
	} while (0)

#include <asm-generic/tlb.h>

#endif
