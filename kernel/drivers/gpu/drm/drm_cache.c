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
 * Authors: Thomas Hellström <thomas-at-tungstengraphics-dot-com>
 */

#include <beep/export.h>
#include <drm/drmP.h>

#if defined(CONFIG_X86)
static void
drm_clflush_page(struct page *page)
{
	uint8_t *page_virtual;
	unsigned int i;
	const int size = boot_cpu_data.x86_clflush_size;

	if (unlikely(page == NULL))
		return;

	page_virtual = kmap_atomic(page);
	for (i = 0; i < PAGE_SIZE; i += size)
		clflush(page_virtual + i);
	kunmap_atomic(page_virtual);
}

static void drm_cache_flush_clflush(struct page *pages[],
				    unsigned long num_pages)
{
	unsigned long i;

	mb();
	for (i = 0; i < num_pages; i++)
		drm_clflush_page(*pages++);
	mb();
}

static void
drm_clflush_ipi_handler(void *null)
{
	wbinvd();
}
#endif

void
drm_clflush_pages(struct page *pages[], unsigned long num_pages)
{

#if defined(CONFIG_X86)
	if (cpu_has_clflush) {
		drm_cache_flush_clflush(pages, num_pages);
		return;
	}

	if (on_each_cpu(drm_clflush_ipi_handler, NULL, 1) != 0)
		printk(KERN_ERR "Timed out waiting for cache flush.\n");

#elif defined(__powerpc__)
	unsigned long i;
	for (i = 0; i < num_pages; i++) {
		struct page *page = pages[i];
		void *page_virtual;

		if (unlikely(page == NULL))
			continue;

		page_virtual = kmap_atomic(page);
		flush_dcache_range((unsigned long)page_virtual,
				   (unsigned long)page_virtual + PAGE_SIZE);
		kunmap_atomic(page_virtual);
	}
#else
	printk(KERN_ERR "Architecture has no drm_cache.c support\n");
	WARN_ON_ONCE(1);
#endif
}
EXPORT_SYMBOL(drm_clflush_pages);

void
drm_clflush_sg(struct sg_table *st)
{
#if defined(CONFIG_X86)
	if (cpu_has_clflush) {
		struct scatterlist *sg;
		int i;

		mb();
		for_each_sg(st->sgl, sg, st->nents, i)
			drm_clflush_page(sg_page(sg));
		mb();

		return;
	}

	if (on_each_cpu(drm_clflush_ipi_handler, NULL, 1) != 0)
		printk(KERN_ERR "Timed out waiting for cache flush.\n");
#else
	printk(KERN_ERR "Architecture has no drm_cache.c support\n");
	WARN_ON_ONCE(1);
#endif
}
EXPORT_SYMBOL(drm_clflush_sg);

void
drm_clflush_virt_range(char *addr, unsigned long length)
{
#if defined(CONFIG_X86)
	if (cpu_has_clflush) {
		char *end = addr + length;
		mb();
		for (; addr < end; addr += boot_cpu_data.x86_clflush_size)
			clflush(addr);
		clflush(end - 1);
		mb();
		return;
	}

	if (on_each_cpu(drm_clflush_ipi_handler, NULL, 1) != 0)
		printk(KERN_ERR "Timed out waiting for cache flush.\n");
#else
	printk(KERN_ERR "Architecture has no drm_cache.c support\n");
	WARN_ON_ONCE(1);
#endif
}
EXPORT_SYMBOL(drm_clflush_virt_range);
