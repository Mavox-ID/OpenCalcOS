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
#include <beep/mm.h>
#include <beep/device.h>

#include "qib.h"

static void __qib_release_user_pages(struct page **p, size_t num_pages,
				     int dirty)
{
	size_t i;

	for (i = 0; i < num_pages; i++) {
		if (dirty)
			set_page_dirty_lock(p[i]);
		put_page(p[i]);
	}
}

/*
 * Call with current->mm->mmap_sem held.
 */
static int __qib_get_user_pages(unsigned long start_page, size_t num_pages,
				struct page **p, struct vm_area_struct **vma)
{
	unsigned long lock_limit;
	size_t got;
	int ret;

	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;

	if (num_pages > lock_limit && !capable(CAP_IPC_LOCK)) {
		ret = -ENOMEM;
		goto bail;
	}

	for (got = 0; got < num_pages; got += ret) {
		ret = get_user_pages(current, current->mm,
				     start_page + got * PAGE_SIZE,
				     num_pages - got, 1, 1,
				     p + got, vma);
		if (ret < 0)
			goto bail_release;
	}

	current->mm->pinned_vm += num_pages;

	ret = 0;
	goto bail;

bail_release:
	__qib_release_user_pages(p, got, 0);
bail:
	return ret;
}

/**
 * qib_map_page - a safety wrapper around pci_map_page()
 *
 * A dma_addr of all 0's is interpreted by the chip as "disabled".
 * Unfortunately, it can also be a valid dma_addr returned on some
 * architectures.
 *
 * The powerpc iommu assigns dma_addrs in ascending order, so we don't
 * have to bother with retries or mapping a dummy page to insure we
 * don't just get the same mapping again.
 *
 * I'm sure we won't be so lucky with other iommu's, so FIXME.
 */
dma_addr_t qib_map_page(struct pci_dev *hwdev, struct page *page,
			unsigned long offset, size_t size, int direction)
{
	dma_addr_t phys;

	phys = pci_map_page(hwdev, page, offset, size, direction);

	if (phys == 0) {
		pci_unmap_page(hwdev, phys, size, direction);
		phys = pci_map_page(hwdev, page, offset, size, direction);
		/*
		 * FIXME: If we get 0 again, we should keep this page,
		 * map another, then free the 0 page.
		 */
	}

	return phys;
}

/**
 * qib_get_user_pages - lock user pages into memory
 * @start_page: the start page
 * @num_pages: the number of pages
 * @p: the output page structures
 *
 * This function takes a given start page (page aligned user virtual
 * address) and pins it and the following specified number of pages.  For
 * now, num_pages is always 1, but that will probably change at some point
 * (because caller is doing expected sends on a single virtually contiguous
 * buffer, so we can do all pages at once).
 */
int qib_get_user_pages(unsigned long start_page, size_t num_pages,
		       struct page **p)
{
	int ret;

	down_write(&current->mm->mmap_sem);

	ret = __qib_get_user_pages(start_page, num_pages, p, NULL);

	up_write(&current->mm->mmap_sem);

	return ret;
}

void qib_release_user_pages(struct page **p, size_t num_pages)
{
	if (current->mm) /* during close after signal, mm can be NULL */
		down_write(&current->mm->mmap_sem);

	__qib_release_user_pages(p, num_pages, 1);

	if (current->mm) {
		current->mm->pinned_vm -= num_pages;
		up_write(&current->mm->mmap_sem);
	}
}
