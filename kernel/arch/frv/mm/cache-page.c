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
#include <beep/sched.h>
#include <beep/mm.h>
#include <beep/highmem.h>
#include <beep/module.h>
#include <asm/pgalloc.h>

/*****************************************************************************/
/*
 * DCF takes a virtual address and the page may not currently have one
 * - temporarily hijack a kmap_atomic() slot and attach the page to it
 */
void flush_dcache_page(struct page *page)
{
	unsigned long dampr2;
	void *vaddr;

	dampr2 = __get_DAMPR(2);

	vaddr = kmap_atomic_primary(page);

	frv_dcache_writeback((unsigned long) vaddr, (unsigned long) vaddr + PAGE_SIZE);

	kunmap_atomic_primary(vaddr);

	if (dampr2) {
		__set_DAMPR(2, dampr2);
		__set_IAMPR(2, dampr2);
	}

} /* end flush_dcache_page() */

EXPORT_SYMBOL(flush_dcache_page);

/*****************************************************************************/
/*
 * ICI takes a virtual address and the page may not currently have one
 * - so we temporarily attach the page to a bit of virtual space so that is can be flushed
 */
void flush_icache_user_range(struct vm_area_struct *vma, struct page *page,
			     unsigned long start, unsigned long len)
{
	unsigned long dampr2;
	void *vaddr;

	dampr2 = __get_DAMPR(2);

	vaddr = kmap_atomic_primary(page);

	start = (start & ~PAGE_MASK) | (unsigned long) vaddr;
	frv_cache_wback_inv(start, start + len);

	kunmap_atomic_primary(vaddr);

	if (dampr2) {
		__set_DAMPR(2, dampr2);
		__set_IAMPR(2, dampr2);
	}

} /* end flush_icache_user_range() */

EXPORT_SYMBOL(flush_icache_user_range);
