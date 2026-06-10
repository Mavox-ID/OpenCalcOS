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
#ifndef __UM_PGTABLE_3LEVEL_H
#define __UM_PGTABLE_3LEVEL_H

#include <asm-generic/pgtable-nopud.h>

/* PGDIR_SHIFT determines what a third-level page table entry can map */

#ifdef CONFIG_64BIT
#define PGDIR_SHIFT	30
#else
#define PGDIR_SHIFT	31
#endif
#define PGDIR_SIZE	(1UL << PGDIR_SHIFT)
#define PGDIR_MASK	(~(PGDIR_SIZE-1))

/* PMD_SHIFT determines the size of the area a second-level page table can
 * map
 */

#define PMD_SHIFT	21
#define PMD_SIZE	(1UL << PMD_SHIFT)
#define PMD_MASK	(~(PMD_SIZE-1))

/*
 * entries per page directory level
 */

#define PTRS_PER_PTE 512
#ifdef CONFIG_64BIT
#define PTRS_PER_PMD 512
#define PTRS_PER_PGD 512
#else
#define PTRS_PER_PMD 1024
#define PTRS_PER_PGD 1024
#endif

#define USER_PTRS_PER_PGD ((TASK_SIZE + (PGDIR_SIZE - 1)) / PGDIR_SIZE)
#define FIRST_USER_ADDRESS	0

#define pte_ERROR(e) \
        printk("%s:%d: bad pte %p(%016lx).\n", __FILE__, __LINE__, &(e), \
	       pte_val(e))
#define pmd_ERROR(e) \
        printk("%s:%d: bad pmd %p(%016lx).\n", __FILE__, __LINE__, &(e), \
	       pmd_val(e))
#define pgd_ERROR(e) \
        printk("%s:%d: bad pgd %p(%016lx).\n", __FILE__, __LINE__, &(e), \
	       pgd_val(e))

#define pud_none(x)	(!(pud_val(x) & ~_PAGE_NEWPAGE))
#define	pud_bad(x)	((pud_val(x) & (~PAGE_MASK & ~_PAGE_USER)) != _KERNPG_TABLE)
#define pud_present(x)	(pud_val(x) & _PAGE_PRESENT)
#define pud_populate(mm, pud, pmd) \
	set_pud(pud, __pud(_PAGE_TABLE + __pa(pmd)))

#ifdef CONFIG_64BIT
#define set_pud(pudptr, pudval) set_64bit((u64 *) (pudptr), pud_val(pudval))
#else
#define set_pud(pudptr, pudval) (*(pudptr) = (pudval))
#endif

static inline int pgd_newpage(pgd_t pgd)
{
	return(pgd_val(pgd) & _PAGE_NEWPAGE);
}

static inline void pgd_mkuptodate(pgd_t pgd) { pgd_val(pgd) &= ~_PAGE_NEWPAGE; }

#ifdef CONFIG_64BIT
#define set_pmd(pmdptr, pmdval) set_64bit((u64 *) (pmdptr), pmd_val(pmdval))
#else
#define set_pmd(pmdptr, pmdval) (*(pmdptr) = (pmdval))
#endif

struct mm_struct;
extern pmd_t *pmd_alloc_one(struct mm_struct *mm, unsigned long address);

static inline void pud_clear (pud_t *pud)
{
	set_pud(pud, __pud(_PAGE_NEWPAGE));
}

#define pud_page(pud) phys_to_page(pud_val(pud) & PAGE_MASK)
#define pud_page_vaddr(pud) ((unsigned long) __va(pud_val(pud) & PAGE_MASK))

/* Find an entry in the second-level page table.. */
#define pmd_offset(pud, address) ((pmd_t *) pud_page_vaddr(*(pud)) + \
			pmd_index(address))

static inline unsigned long pte_pfn(pte_t pte)
{
	return phys_to_pfn(pte_val(pte));
}

static inline pte_t pfn_pte(pfn_t page_nr, pgprot_t pgprot)
{
	pte_t pte;
	phys_t phys = pfn_to_phys(page_nr);

	pte_set_val(pte, phys, pgprot);
	return pte;
}

static inline pmd_t pfn_pmd(pfn_t page_nr, pgprot_t pgprot)
{
	return __pmd((page_nr << PAGE_SHIFT) | pgprot_val(pgprot));
}

/*
 * Bits 0 through 3 are taken in the low part of the pte,
 * put the 32 bits of offset into the high part.
 */
#define PTE_FILE_MAX_BITS	32

#ifdef CONFIG_64BIT

#define pte_to_pgoff(p) ((p).pte >> 32)

#define pgoff_to_pte(off) ((pte_t) { ((off) << 32) | _PAGE_FILE })

#else

#define pte_to_pgoff(pte) ((pte).pte_high)

#define pgoff_to_pte(off) ((pte_t) { _PAGE_FILE, (off) })

#endif

#endif

