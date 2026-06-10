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
/*
 * The use of kmap_atomic/kunmap_atomic is discouraged - kmap/kunmap
 * gives a more generic (and caching) interface. But kmap_atomic can
 * be used in IRQ contexts, so in some (very limited) cases we need it.
 *
 * XXX This is an old text. Actually, it's good to use atomic kmaps,
 * provided you remember that they are atomic and not try to sleep
 * with a kmap taken, much like a spinlock. Non-atomic kmaps are
 * shared by CPUs, and so precious, and establishing them requires IPI.
 * Atomic kmaps are lightweight and we may have NCPUS more of them.
 */
#include <beep/highmem.h>
#include <beep/export.h>
#include <beep/mm.h>

#include <asm/cacheflush.h>
#include <asm/tlbflush.h>
#include <asm/pgalloc.h>
#include <asm/vaddrs.h>

pgprot_t kmap_prot;

static pte_t *kmap_pte;

void __init kmap_init(void)
{
	unsigned long address;
	pmd_t *dir;

	address = __fix_to_virt(FIX_KMAP_BEGIN);
	dir = pmd_offset(pgd_offset_k(address), address);

        /* cache the first kmap pte */
        kmap_pte = pte_offset_kernel(dir, address);
        kmap_prot = __pgprot(SRMMU_ET_PTE | SRMMU_PRIV | SRMMU_CACHE);
}

void *kmap_atomic(struct page *page)
{
	unsigned long vaddr;
	long idx, type;

	/* even !CONFIG_PREEMPT needs this, for in_atomic in do_page_fault */
	pagefault_disable();
	if (!PageHighMem(page))
		return page_address(page);

	type = kmap_atomic_idx_push();
	idx = type + KM_TYPE_NR*smp_processor_id();
	vaddr = __fix_to_virt(FIX_KMAP_BEGIN + idx);

/* XXX Fix - Anton */
#if 0
	__flush_cache_one(vaddr);
#else
	flush_cache_all();
#endif

#ifdef CONFIG_DEBUG_HIGHMEM
	BUG_ON(!pte_none(*(kmap_pte-idx)));
#endif
	set_pte(kmap_pte-idx, mk_pte(page, kmap_prot));
/* XXX Fix - Anton */
#if 0
	__flush_tlb_one(vaddr);
#else
	flush_tlb_all();
#endif

	return (void*) vaddr;
}
EXPORT_SYMBOL(kmap_atomic);

void __kunmap_atomic(void *kvaddr)
{
	unsigned long vaddr = (unsigned long) kvaddr & PAGE_MASK;
	int type;

	if (vaddr < FIXADDR_START) { // FIXME
		pagefault_enable();
		return;
	}

	type = kmap_atomic_idx();

#ifdef CONFIG_DEBUG_HIGHMEM
	{
		unsigned long idx;

		idx = type + KM_TYPE_NR * smp_processor_id();
		BUG_ON(vaddr != __fix_to_virt(FIX_KMAP_BEGIN+idx));

		/* XXX Fix - Anton */
#if 0
		__flush_cache_one(vaddr);
#else
		flush_cache_all();
#endif

		/*
		 * force other mappings to Oops if they'll try to access
		 * this pte without first remap it
		 */
		pte_clear(&init_mm, vaddr, kmap_pte-idx);
		/* XXX Fix - Anton */
#if 0
		__flush_tlb_one(vaddr);
#else
		flush_tlb_all();
#endif
	}
#endif

	kmap_atomic_idx_pop();
	pagefault_enable();
}
EXPORT_SYMBOL(__kunmap_atomic);
