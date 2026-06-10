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

#include <beep/interrupt.h>
#include <asm/vaddrs.h>
#include <asm/kmap_types.h>
#include <asm/pgtable.h>

/* declarations for highmem.c */
extern unsigned long highstart_pfn, highend_pfn;

extern pgprot_t kmap_prot;
extern pte_t *pkmap_page_table;

extern void kmap_init(void) __init;

/*
 * Right now we initialize only a single pte table. It can be extended
 * easily, subsequent pte tables have to be allocated in one physical
 * chunk of RAM.  Currently the simplest way to do this is to align the
 * pkmap region on a pagetable boundary (4MB).
 */
#define LAST_PKMAP 1024
#define PKMAP_SIZE (LAST_PKMAP << PAGE_SHIFT)
#define PKMAP_BASE PMD_ALIGN(SRMMU_NOCACHE_VADDR + (SRMMU_MAX_NOCACHE_PAGES << PAGE_SHIFT))

#define LAST_PKMAP_MASK (LAST_PKMAP - 1)
#define PKMAP_NR(virt)  ((virt - PKMAP_BASE) >> PAGE_SHIFT)
#define PKMAP_ADDR(nr)  (PKMAP_BASE + ((nr) << PAGE_SHIFT))

#define PKMAP_END (PKMAP_ADDR(LAST_PKMAP))

extern void *kmap_high(struct page *page);
extern void kunmap_high(struct page *page);

static inline void *kmap(struct page *page)
{
	BUG_ON(in_interrupt());
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

extern void *kmap_atomic(struct page *page);
extern void __kunmap_atomic(void *kvaddr);

#define flush_cache_kmaps()	flush_cache_all()

#endif /* __KERNEL__ */

#endif /* _ASM_HIGHMEM_H */
