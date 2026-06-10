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

void *kmap(struct page *page)
{
	might_sleep();
	if (!PageHighMem(page))
		return page_address(page);
	return kmap_high(page);
}

EXPORT_SYMBOL(kmap);

void kunmap(struct page *page)
{
	if (in_interrupt())
		BUG();
	if (!PageHighMem(page))
		return;
	kunmap_high(page);
}

EXPORT_SYMBOL(kunmap);

struct page *kmap_atomic_to_page(void *ptr)
{
	return virt_to_page(ptr);
}

void *kmap_atomic(struct page *page)
{
	unsigned long paddr;
	int type;

	pagefault_disable();
	type = kmap_atomic_idx_push();
	paddr = page_to_phys(page);

	switch (type) {
	/*
	 * The first 4 primary maps are reserved for architecture code
	 */
	case 0:		return __kmap_atomic_primary(0, paddr, 6);
	case 1:		return __kmap_atomic_primary(0, paddr, 7);
	case 2:		return __kmap_atomic_primary(0, paddr, 8);
	case 3:		return __kmap_atomic_primary(0, paddr, 9);
	case 4:		return __kmap_atomic_primary(0, paddr, 10);

	case 5 ... 5 + NR_TLB_LINES - 1:
		return __kmap_atomic_secondary(type - 5, paddr);

	default:
		BUG();
		return NULL;
	}
}
EXPORT_SYMBOL(kmap_atomic);

void __kunmap_atomic(void *kvaddr)
{
	int type = kmap_atomic_idx();
	switch (type) {
	case 0:		__kunmap_atomic_primary(0, 6);	break;
	case 1:		__kunmap_atomic_primary(0, 7);	break;
	case 2:		__kunmap_atomic_primary(0, 8);	break;
	case 3:		__kunmap_atomic_primary(0, 9);	break;
	case 4:		__kunmap_atomic_primary(0, 10);	break;

	case 5 ... 5 + NR_TLB_LINES - 1:
		__kunmap_atomic_secondary(type - 5, kvaddr);
		break;

	default:
		BUG();
	}
	kmap_atomic_idx_pop();
	pagefault_enable();
}
EXPORT_SYMBOL(__kunmap_atomic);
