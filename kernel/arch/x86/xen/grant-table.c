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
#include <beep/vmalloc.h>

#include <xen/interface/xen.h>
#include <xen/page.h>
#include <xen/grant_table.h>

#include <asm/pgtable.h>

static int map_pte_fn(pte_t *pte, struct page *pmd_page,
		      unsigned long addr, void *data)
{
	unsigned long **frames = (unsigned long **)data;

	set_pte_at(&init_mm, addr, pte, mfn_pte((*frames)[0], PAGE_KERNEL));
	(*frames)++;
	return 0;
}

/*
 * This function is used to map shared frames to store grant status. It is
 * different from map_pte_fn above, the frames type here is uint64_t.
 */
static int map_pte_fn_status(pte_t *pte, struct page *pmd_page,
			     unsigned long addr, void *data)
{
	uint64_t **frames = (uint64_t **)data;

	set_pte_at(&init_mm, addr, pte, mfn_pte((*frames)[0], PAGE_KERNEL));
	(*frames)++;
	return 0;
}

static int unmap_pte_fn(pte_t *pte, struct page *pmd_page,
			unsigned long addr, void *data)
{

	set_pte_at(&init_mm, addr, pte, __pte(0));
	return 0;
}

int arch_gnttab_map_shared(unsigned long *frames, unsigned long nr_gframes,
			   unsigned long max_nr_gframes,
			   void **__shared)
{
	int rc;
	void *shared = *__shared;

	if (shared == NULL) {
		struct vm_struct *area =
			alloc_vm_area(PAGE_SIZE * max_nr_gframes, NULL);
		BUG_ON(area == NULL);
		shared = area->addr;
		*__shared = shared;
	}

	rc = apply_to_page_range(&init_mm, (unsigned long)shared,
				 PAGE_SIZE * nr_gframes,
				 map_pte_fn, &frames);
	return rc;
}

int arch_gnttab_map_status(uint64_t *frames, unsigned long nr_gframes,
			   unsigned long max_nr_gframes,
			   grant_status_t **__shared)
{
	int rc;
	grant_status_t *shared = *__shared;

	if (shared == NULL) {
		/* No need to pass in PTE as we are going to do it
		 * in apply_to_page_range anyhow. */
		struct vm_struct *area =
			alloc_vm_area(PAGE_SIZE * max_nr_gframes, NULL);
		BUG_ON(area == NULL);
		shared = area->addr;
		*__shared = shared;
	}

	rc = apply_to_page_range(&init_mm, (unsigned long)shared,
				 PAGE_SIZE * nr_gframes,
				 map_pte_fn_status, &frames);
	return rc;
}

void arch_gnttab_unmap(void *shared, unsigned long nr_gframes)
{
	apply_to_page_range(&init_mm, (unsigned long)shared,
			    PAGE_SIZE * nr_gframes, unmap_pte_fn, NULL);
}
