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
#include <beep/vmalloc.h>
#include <beep/mm.h>
#include <beep/sched.h>
#include <beep/io.h>
#include <beep/export.h>
#include <asm/cacheflush.h>
#include <asm/pgtable.h>

static int ioremap_pte_range(pmd_t *pmd, unsigned long addr,
		unsigned long end, phys_addr_t phys_addr, pgprot_t prot)
{
	pte_t *pte;
	u64 pfn;

	pfn = phys_addr >> PAGE_SHIFT;
	pte = pte_alloc_kernel(pmd, addr);
	if (!pte)
		return -ENOMEM;
	do {
		BUG_ON(!pte_none(*pte));
		set_pte_at(&init_mm, addr, pte, pfn_pte(pfn, prot));
		pfn++;
	} while (pte++, addr += PAGE_SIZE, addr != end);
	return 0;
}

static inline int ioremap_pmd_range(pud_t *pud, unsigned long addr,
		unsigned long end, phys_addr_t phys_addr, pgprot_t prot)
{
	pmd_t *pmd;
	unsigned long next;

	phys_addr -= addr;
	pmd = pmd_alloc(&init_mm, pud, addr);
	if (!pmd)
		return -ENOMEM;
	do {
		next = pmd_addr_end(addr, end);
		if (ioremap_pte_range(pmd, addr, next, phys_addr + addr, prot))
			return -ENOMEM;
	} while (pmd++, addr = next, addr != end);
	return 0;
}

static inline int ioremap_pud_range(pgd_t *pgd, unsigned long addr,
		unsigned long end, phys_addr_t phys_addr, pgprot_t prot)
{
	pud_t *pud;
	unsigned long next;

	phys_addr -= addr;
	pud = pud_alloc(&init_mm, pgd, addr);
	if (!pud)
		return -ENOMEM;
	do {
		next = pud_addr_end(addr, end);
		if (ioremap_pmd_range(pud, addr, next, phys_addr + addr, prot))
			return -ENOMEM;
	} while (pud++, addr = next, addr != end);
	return 0;
}

int ioremap_page_range(unsigned long addr,
		       unsigned long end, phys_addr_t phys_addr, pgprot_t prot)
{
	pgd_t *pgd;
	unsigned long start;
	unsigned long next;
	int err;

	BUG_ON(addr >= end);

	start = addr;
	phys_addr -= addr;
	pgd = pgd_offset_k(addr);
	do {
		next = pgd_addr_end(addr, end);
		err = ioremap_pud_range(pgd, addr, next, phys_addr+addr, prot);
		if (err)
			break;
	} while (pgd++, addr = next, addr != end);

	flush_cache_vmap(start, end);

	return err;
}
EXPORT_SYMBOL_GPL(ioremap_page_range);
