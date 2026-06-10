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
#include <beep/signal.h>
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/string.h>
#include <beep/types.h>
#include <beep/ptrace.h>
#include <beep/bootmem.h>
#include <beep/swap.h>
#include <beep/pagemap.h>

#include <asm/bootparam.h>
#include <asm/mmu_context.h>
#include <asm/tlb.h>
#include <asm/tlbflush.h>
#include <asm/page.h>
#include <asm/pgalloc.h>
#include <asm/pgtable.h>

//#define printd(x...) printk(x)
#define printd(x...) do { } while(0)

/* 
 * Note:
 * The kernel provides one architecture bit PG_arch_1 in the page flags that 
 * can be used for cache coherency.
 *
 * I$-D$ coherency.
 *
 * The Xtensa architecture doesn't keep the instruction cache coherent with
 * the data cache. We use the architecture bit to indicate if the caches
 * are coherent. The kernel clears this bit whenever a page is added to the
 * page cache. At that time, the caches might not be in sync. We, therefore,
 * define this flag as 'clean' if set.
 *
 * D-cache aliasing.
 *
 * With cache aliasing, we have to always flush the cache when pages are
 * unmapped (see tlb_start_vma(). So, we use this flag to indicate a dirty
 * page.
 * 
 *
 *
 */

#if (DCACHE_WAY_SIZE > PAGE_SIZE) && XCHAL_DCACHE_IS_WRITEBACK

/*
 * Any time the kernel writes to a user page cache page, or it is about to
 * read from a page cache page this routine is called.
 *
 */

void flush_dcache_page(struct page *page)
{
	struct address_space *mapping = page_mapping(page);

	/*
	 * If we have a mapping but the page is not mapped to user-space
	 * yet, we simply mark this page dirty and defer flushing the 
	 * caches until update_mmu().
	 */

	if (mapping && !mapping_mapped(mapping)) {
		if (!test_bit(PG_arch_1, &page->flags))
			set_bit(PG_arch_1, &page->flags);
		return;

	} else {

		unsigned long phys = page_to_phys(page);
		unsigned long temp = page->index << PAGE_SHIFT;
		unsigned long alias = !(DCACHE_ALIAS_EQ(temp, phys));
		unsigned long virt;

		/* 
		 * Flush the page in kernel space and user space.
		 * Note that we can omit that step if aliasing is not
		 * an issue, but we do have to synchronize I$ and D$
		 * if we have a mapping.
		 */

		if (!alias && !mapping)
			return;

		__flush_invalidate_dcache_page((long)page_address(page));

		virt = TLBTEMP_BASE_1 + (temp & DCACHE_ALIAS_MASK);

		if (alias)
			__flush_invalidate_dcache_page_alias(virt, phys);

		if (mapping)
			__invalidate_icache_page_alias(virt, phys);
	}

	/* There shouldn't be an entry in the cache for this page anymore. */
}


/*
 * For now, flush the whole cache. FIXME??
 */

void flush_cache_range(struct vm_area_struct* vma,
		       unsigned long start, unsigned long end)
{
	__flush_invalidate_dcache_all();
	__invalidate_icache_all();
}

/* 
 * Remove any entry in the cache for this page. 
 *
 * Note that this function is only called for user pages, so use the
 * alias versions of the cache flush functions.
 */

void flush_cache_page(struct vm_area_struct* vma, unsigned long address,
		      unsigned long pfn)
{
	/* Note that we have to use the 'alias' address to avoid multi-hit */

	unsigned long phys = page_to_phys(pfn_to_page(pfn));
	unsigned long virt = TLBTEMP_BASE_1 + (address & DCACHE_ALIAS_MASK);

	__flush_invalidate_dcache_page_alias(virt, phys);
	__invalidate_icache_page_alias(virt, phys);
}

#endif

void
update_mmu_cache(struct vm_area_struct * vma, unsigned long addr, pte_t *ptep)
{
	unsigned long pfn = pte_pfn(*ptep);
	struct page *page;

	if (!pfn_valid(pfn))
		return;

	page = pfn_to_page(pfn);

	/* Invalidate old entry in TLBs */

	invalidate_itlb_mapping(addr);
	invalidate_dtlb_mapping(addr);

#if (DCACHE_WAY_SIZE > PAGE_SIZE) && XCHAL_DCACHE_IS_WRITEBACK

	if (!PageReserved(page) && test_bit(PG_arch_1, &page->flags)) {

		unsigned long paddr = (unsigned long) page_address(page);
		unsigned long phys = page_to_phys(page);
		unsigned long tmp = TLBTEMP_BASE_1 + (addr & DCACHE_ALIAS_MASK);

		__flush_invalidate_dcache_page(paddr);

		__flush_invalidate_dcache_page_alias(tmp, phys);
		__invalidate_icache_page_alias(tmp, phys);

		clear_bit(PG_arch_1, &page->flags);
	}
#else
	if (!PageReserved(page) && !test_bit(PG_arch_1, &page->flags)
	    && (vma->vm_flags & VM_EXEC) != 0) {
	    	unsigned long paddr = (unsigned long) page_address(page);
		__flush_dcache_page(paddr);
		__invalidate_icache_page(paddr);
		set_bit(PG_arch_1, &page->flags);
	}
#endif
}

/*
 * access_process_vm() has called get_user_pages(), which has done a
 * flush_dcache_page() on the page.
 */

#if (DCACHE_WAY_SIZE > PAGE_SIZE) && XCHAL_DCACHE_IS_WRITEBACK

void copy_to_user_page(struct vm_area_struct *vma, struct page *page,
		unsigned long vaddr, void *dst, const void *src,
		unsigned long len)
{
	unsigned long phys = page_to_phys(page);
	unsigned long alias = !(DCACHE_ALIAS_EQ(vaddr, phys));

	/* Flush and invalidate user page if aliased. */

	if (alias) {
		unsigned long t = TLBTEMP_BASE_1 + (vaddr & DCACHE_ALIAS_MASK);
		__flush_invalidate_dcache_page_alias(t, phys);
	}

	/* Copy data */
	
	memcpy(dst, src, len);

	/*
	 * Flush and invalidate kernel page if aliased and synchronize 
	 * data and instruction caches for executable pages. 
	 */

	if (alias) {
		unsigned long t = TLBTEMP_BASE_1 + (vaddr & DCACHE_ALIAS_MASK);

		__flush_invalidate_dcache_range((unsigned long) dst, len);
		if ((vma->vm_flags & VM_EXEC) != 0)
			__invalidate_icache_page_alias(t, phys);

	} else if ((vma->vm_flags & VM_EXEC) != 0) {
		__flush_dcache_range((unsigned long)dst,len);
		__invalidate_icache_range((unsigned long) dst, len);
	}
}

extern void copy_from_user_page(struct vm_area_struct *vma, struct page *page,
		unsigned long vaddr, void *dst, const void *src,
		unsigned long len)
{
	unsigned long phys = page_to_phys(page);
	unsigned long alias = !(DCACHE_ALIAS_EQ(vaddr, phys));

	/*
	 * Flush user page if aliased. 
	 * (Note: a simply flush would be sufficient) 
	 */

	if (alias) {
		unsigned long t = TLBTEMP_BASE_1 + (vaddr & DCACHE_ALIAS_MASK);
		__flush_invalidate_dcache_page_alias(t, phys);
	}

	memcpy(dst, src, len);
}

#endif
