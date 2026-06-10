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
#ifndef _ASM_HIGHMEM_H
#define _ASM_HIGHMEM_H

#ifdef __KERNEL__

#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/uaccess.h>
#include <asm/fixmap.h>

extern pte_t *kmap_pte;
extern pgprot_t kmap_prot;
extern pte_t *pkmap_page_table;

/*
 * Right now we initialize only a single pte table. It can be extended
 * easily, subsequent pte tables have to be allocated in one physical
 * chunk of RAM.
 */
/*
 * We use one full pte table with 4K pages. And with 16K/64K/256K pages pte
 * table covers enough memory (32MB/512MB/2GB resp.), so that both FIXMAP
 * and PKMAP can be placed in a single pte table. We use 512 pages for PKMAP
 * in case of 16K/64K/256K page sizes.
 */

#define PKMAP_ORDER	PTE_SHIFT
#define LAST_PKMAP	(1 << PKMAP_ORDER)

#define PKMAP_BASE	((FIXADDR_START - PAGE_SIZE * (LAST_PKMAP + 1)) \
								& PMD_MASK)

#define LAST_PKMAP_MASK	(LAST_PKMAP - 1)
#define PKMAP_NR(virt)  ((virt - PKMAP_BASE) >> PAGE_SHIFT)
#define PKMAP_ADDR(nr)  (PKMAP_BASE + ((nr) << PAGE_SHIFT))

extern void *kmap_high(struct page *page);
extern void kunmap_high(struct page *page);
extern void *kmap_atomic_prot(struct page *page, pgprot_t prot);
extern void __kunmap_atomic(void *kvaddr);

static inline void *kmap(struct page *page)
{
	might_sleep();
	if (!PageHighMem(page))
		return page_address(page);
	return kmap_high(page);
}

static inline void kunmap(struct page *page)
{
	BUG_ON(in_interrupt());
	if (!PageHighMem(page))
		return;
	kunmap_high(page);
}

static inline void *kmap_atomic(struct page *page)
{
	return kmap_atomic_prot(page, kmap_prot);
}

static inline struct page *kmap_atomic_to_page(void *ptr)
{
	unsigned long idx, vaddr = (unsigned long) ptr;
	pte_t *pte;

	if (vaddr < FIXADDR_START)
		return virt_to_page(ptr);

	idx = virt_to_fix(vaddr);
	pte = kmap_pte - (idx - FIX_KMAP_BEGIN);
	return pte_page(*pte);
}

#define flush_cache_kmaps()	{ flush_icache(); flush_dcache(); }

#endif /* __KERNEL__ */

#endif /* _ASM_HIGHMEM_H */
