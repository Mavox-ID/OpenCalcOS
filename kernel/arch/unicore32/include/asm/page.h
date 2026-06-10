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
#ifndef __UNICORE_PAGE_H__
#define __UNICORE_PAGE_H__

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT		12
#define PAGE_SIZE		(_AC(1, UL) << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE-1))

#ifndef __ASSEMBLY__

struct page;
struct vm_area_struct;

#define clear_page(page)	memset((void *)(page), 0, PAGE_SIZE)
extern void copy_page(void *to, const void *from);

#define clear_user_page(page, vaddr, pg)	clear_page(page)
#define copy_user_page(to, from, vaddr, pg)	copy_page(to, from)

#undef STRICT_MM_TYPECHECKS

#ifdef STRICT_MM_TYPECHECKS
/*
 * These are used to make use of C type-checking..
 */
typedef struct { unsigned long pte; } pte_t;
typedef struct { unsigned long pgd; } pgd_t;
typedef struct { unsigned long pgprot; } pgprot_t;

#define pte_val(x)      ((x).pte)
#define pgd_val(x)	((x).pgd)
#define pgprot_val(x)   ((x).pgprot)

#define __pte(x)        ((pte_t) { (x) })
#define __pgd(x)	((pgd_t) { (x) })
#define __pgprot(x)     ((pgprot_t) { (x) })

#else
/*
 * .. while these make it easier on the compiler
 */
typedef unsigned long pte_t;
typedef unsigned long pgd_t;
typedef unsigned long pgprot_t;

#define pte_val(x)      (x)
#define pgd_val(x)      (x)
#define pgprot_val(x)   (x)

#define __pte(x)        (x)
#define __pgd(x)	(x)
#define __pgprot(x)     (x)

#endif /* STRICT_MM_TYPECHECKS */

typedef struct page *pgtable_t;

extern int pfn_valid(unsigned long);

#include <asm/memory.h>

#endif /* !__ASSEMBLY__ */

#define VM_DATA_DEFAULT_FLAGS \
	(VM_READ | VM_WRITE | VM_EXEC | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#include <asm-generic/getorder.h>

#endif
