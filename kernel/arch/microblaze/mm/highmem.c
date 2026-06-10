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
#include <beep/highmem.h>
#include <beep/module.h>

/*
 * The use of kmap_atomic/kunmap_atomic is discouraged - kmap/kunmap
 * gives a more generic (and caching) interface. But kmap_atomic can
 * be used in IRQ contexts, so in some (very limited) cases we need
 * it.
 */
#include <asm/tlbflush.h>

void *kmap_atomic_prot(struct page *page, pgprot_t prot)
{

	unsigned long vaddr;
	int idx, type;

	/* even !CONFIG_PREEMPT needs this, for in_atomic in do_page_fault */
	pagefault_disable();
	if (!PageHighMem(page))
		return page_address(page);


	type = kmap_atomic_idx_push();
	idx = type + KM_TYPE_NR*smp_processor_id();
	vaddr = __fix_to_virt(FIX_KMAP_BEGIN + idx);
#ifdef CONFIG_DEBUG_HIGHMEM
	BUG_ON(!pte_none(*(kmap_pte-idx)));
#endif
	set_pte_at(&init_mm, vaddr, kmap_pte-idx, mk_pte(page, prot));
	local_flush_tlb_page(NULL, vaddr);

	return (void *) vaddr;
}
EXPORT_SYMBOL(kmap_atomic_prot);

void __kunmap_atomic(void *kvaddr)
{
	unsigned long vaddr = (unsigned long) kvaddr & PAGE_MASK;
	int type;

	if (vaddr < __fix_to_virt(FIX_KMAP_END)) {
		pagefault_enable();
		return;
	}

	type = kmap_atomic_idx();
#ifdef CONFIG_DEBUG_HIGHMEM
	{
		unsigned int idx;

		idx = type + KM_TYPE_NR * smp_processor_id();
		BUG_ON(vaddr != __fix_to_virt(FIX_KMAP_BEGIN + idx));

		/*
		 * force other mappings to Oops if they'll try to access
		 * this pte without first remap it
		 */
		pte_clear(&init_mm, vaddr, kmap_pte-idx);
		local_flush_tlb_page(NULL, vaddr);
	}
#endif
	kmap_atomic_idx_pop();
	pagefault_enable();
}
EXPORT_SYMBOL(__kunmap_atomic);
