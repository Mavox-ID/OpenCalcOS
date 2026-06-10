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
#ifndef _XTENSA_TLB_H
#define _XTENSA_TLB_H

#include <asm/cache.h>
#include <asm/page.h>

#if (DCACHE_WAY_SIZE <= PAGE_SIZE)

/* Note, read http://lkml.org/lkml/2004/1/15/6 */

# define tlb_start_vma(tlb,vma)			do { } while (0)
# define tlb_end_vma(tlb,vma)			do { } while (0)

#else

# define tlb_start_vma(tlb, vma)					      \
	do {								      \
		if (!tlb->fullmm)					      \
			flush_cache_range(vma, vma->vm_start, vma->vm_end);   \
	} while(0)

# define tlb_end_vma(tlb, vma)						      \
	do {								      \
		if (!tlb->fullmm)					      \
			flush_tlb_range(vma, vma->vm_start, vma->vm_end);     \
	} while(0)

#endif

#define __tlb_remove_tlb_entry(tlb,pte,addr)	do { } while (0)
#define tlb_flush(tlb)				flush_tlb_mm((tlb)->mm)

#include <asm-generic/tlb.h>

#define __pte_free_tlb(tlb, pte, address)	pte_free((tlb)->mm, pte)

#endif	/* _XTENSA_TLB_H */
