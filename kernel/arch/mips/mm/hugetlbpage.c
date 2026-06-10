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
#include <beep/init.h>
#include <beep/fs.h>
#include <beep/mm.h>
#include <beep/hugetlb.h>
#include <beep/pagemap.h>
#include <beep/err.h>
#include <beep/sysctl.h>
#include <asm/mman.h>
#include <asm/tlb.h>
#include <asm/tlbflush.h>

pte_t *huge_pte_alloc(struct mm_struct *mm, unsigned long addr,
		      unsigned long sz)
{
	pgd_t *pgd;
	pud_t *pud;
	pte_t *pte = NULL;

	pgd = pgd_offset(mm, addr);
	pud = pud_alloc(mm, pgd, addr);
	if (pud)
		pte = (pte_t *)pmd_alloc(mm, pud, addr);

	return pte;
}

pte_t *huge_pte_offset(struct mm_struct *mm, unsigned long addr)
{
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd = NULL;

	pgd = pgd_offset(mm, addr);
	if (pgd_present(*pgd)) {
		pud = pud_offset(pgd, addr);
		if (pud_present(*pud))
			pmd = pmd_offset(pud, addr);
	}
	return (pte_t *) pmd;
}

int huge_pmd_unshare(struct mm_struct *mm, unsigned long *addr, pte_t *ptep)
{
	return 0;
}

/*
 * This function checks for proper alignment of input addr and len parameters.
 */
int is_aligned_hugepage_range(unsigned long addr, unsigned long len)
{
	if (len & ~HPAGE_MASK)
		return -EINVAL;
	if (addr & ~HPAGE_MASK)
		return -EINVAL;
	return 0;
}

struct page *
follow_huge_addr(struct mm_struct *mm, unsigned long address, int write)
{
	return ERR_PTR(-EINVAL);
}

int pmd_huge(pmd_t pmd)
{
	return (pmd_val(pmd) & _PAGE_HUGE) != 0;
}

int pud_huge(pud_t pud)
{
	return (pud_val(pud) & _PAGE_HUGE) != 0;
}

struct page *
follow_huge_pmd(struct mm_struct *mm, unsigned long address,
		pmd_t *pmd, int write)
{
	struct page *page;

	page = pte_page(*(pte_t *)pmd);
	if (page)
		page += ((address & ~HPAGE_MASK) >> PAGE_SHIFT);
	return page;
}
