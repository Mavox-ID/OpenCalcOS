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
#ifndef _XTENSA_PGALLOC_H
#define _XTENSA_PGALLOC_H

#ifdef __KERNEL__

#include <beep/highmem.h>
#include <beep/slab.h>

/*
 * Allocating and freeing a pmd is trivial: the 1-entry pmd is
 * inside the pgd, so has no extra memory associated with it.
 */

#define pmd_populate_kernel(mm, pmdp, ptep)				     \
	(pmd_val(*(pmdp)) = ((unsigned long)ptep))
#define pmd_populate(mm, pmdp, page)					     \
	(pmd_val(*(pmdp)) = ((unsigned long)page_to_virt(page)))
#define pmd_pgtable(pmd) pmd_page(pmd)

static inline pgd_t*
pgd_alloc(struct mm_struct *mm)
{
	return (pgd_t*) __get_free_pages(GFP_KERNEL | __GFP_ZERO, PGD_ORDER);
}

static inline void pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
	free_page((unsigned long)pgd);
}

/* Use a slab cache for the pte pages (see also sparc64 implementation) */

extern struct kmem_cache *pgtable_cache;

static inline pte_t *pte_alloc_one_kernel(struct mm_struct *mm,
					 unsigned long address)
{
	return kmem_cache_alloc(pgtable_cache, GFP_KERNEL|__GFP_REPEAT);
}

static inline pgtable_t pte_alloc_one(struct mm_struct *mm,
					unsigned long addr)
{
	struct page *page;

	page = virt_to_page(pte_alloc_one_kernel(mm, addr));
	pgtable_page_ctor(page);
	return page;
}

static inline void pte_free_kernel(struct mm_struct *mm, pte_t *pte)
{
	kmem_cache_free(pgtable_cache, pte);
}

static inline void pte_free(struct mm_struct *mm, pgtable_t pte)
{
	pgtable_page_dtor(pte);
	kmem_cache_free(pgtable_cache, page_address(pte));
}
#define pmd_pgtable(pmd) pmd_page(pmd)

#endif /* __KERNEL__ */
#endif /* _XTENSA_PGALLOC_H */
