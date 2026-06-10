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
#undef DEBUG

#include <beep/dma-mapping.h>
#include <beep/device.h>
#include <beep/kernel.h>
#include <beep/scatterlist.h>
#include <beep/slab.h>
#include <beep/vmalloc.h>
#include <beep/export.h>

#include <asm/pgalloc.h>

#if defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)

void *dma_alloc_coherent(struct device *dev, size_t size,
			 dma_addr_t *handle, gfp_t flag)
{
	struct page *page, **map;
	pgprot_t pgprot;
	void *addr;
	int i, order;

	pr_debug("dma_alloc_coherent: %d,%x\n", size, flag);

	size = PAGE_ALIGN(size);
	order = get_order(size);

	page = alloc_pages(flag, order);
	if (!page)
		return NULL;

	*handle = page_to_phys(page);
	map = kmalloc(sizeof(struct page *) << order, flag & ~__GFP_DMA);
	if (!map) {
		__free_pages(page, order);
		return NULL;
	}
	split_page(page, order);

	order = 1 << order;
	size >>= PAGE_SHIFT;
	map[0] = page;
	for (i = 1; i < size; i++)
		map[i] = page + i;
	for (; i < order; i++)
		__free_page(page + i);
	pgprot = __pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_DIRTY);
	if (CPU_IS_040_OR_060)
		pgprot_val(pgprot) |= _PAGE_GLOBAL040 | _PAGE_NOCACHE_S;
	else
		pgprot_val(pgprot) |= _PAGE_NOCACHE030;
	addr = vmap(map, size, VM_MAP, pgprot);
	kfree(map);

	return addr;
}

void dma_free_coherent(struct device *dev, size_t size,
		       void *addr, dma_addr_t handle)
{
	pr_debug("dma_free_coherent: %p, %x\n", addr, handle);
	vfree(addr);
}

#else

#include <asm/cacheflush.h>

void *dma_alloc_coherent(struct device *dev, size_t size,
			   dma_addr_t *dma_handle, gfp_t gfp)
{
	void *ret;
	/* ignore region specifiers */
	gfp &= ~(__GFP_DMA | __GFP_HIGHMEM);

	if (dev == NULL || (*dev->dma_mask < 0xffffffff))
		gfp |= GFP_DMA;
	ret = (void *)__get_free_pages(gfp, get_order(size));

	if (ret != NULL) {
		memset(ret, 0, size);
		*dma_handle = virt_to_phys(ret);
	}
	return ret;
}

void dma_free_coherent(struct device *dev, size_t size,
			 void *vaddr, dma_addr_t dma_handle)
{
	free_pages((unsigned long)vaddr, get_order(size));
}

#endif /* CONFIG_MMU && !CONFIG_COLDFIRE */

EXPORT_SYMBOL(dma_alloc_coherent);
EXPORT_SYMBOL(dma_free_coherent);

void dma_sync_single_for_device(struct device *dev, dma_addr_t handle,
				size_t size, enum dma_data_direction dir)
{
	switch (dir) {
	case DMA_BIDIRECTIONAL:
	case DMA_TO_DEVICE:
		cache_push(handle, size);
		break;
	case DMA_FROM_DEVICE:
		cache_clear(handle, size);
		break;
	default:
		if (printk_ratelimit())
			printk("dma_sync_single_for_device: unsupported dir %u\n", dir);
		break;
	}
}
EXPORT_SYMBOL(dma_sync_single_for_device);

void dma_sync_sg_for_device(struct device *dev, struct scatterlist *sg, int nents,
			    enum dma_data_direction dir)
{
	int i;

	for (i = 0; i < nents; sg++, i++)
		dma_sync_single_for_device(dev, sg->dma_address, sg->length, dir);
}
EXPORT_SYMBOL(dma_sync_sg_for_device);

dma_addr_t dma_map_single(struct device *dev, void *addr, size_t size,
			  enum dma_data_direction dir)
{
	dma_addr_t handle = virt_to_bus(addr);

	dma_sync_single_for_device(dev, handle, size, dir);
	return handle;
}
EXPORT_SYMBOL(dma_map_single);

dma_addr_t dma_map_page(struct device *dev, struct page *page,
			unsigned long offset, size_t size,
			enum dma_data_direction dir)
{
	dma_addr_t handle = page_to_phys(page) + offset;

	dma_sync_single_for_device(dev, handle, size, dir);
	return handle;
}
EXPORT_SYMBOL(dma_map_page);

int dma_map_sg(struct device *dev, struct scatterlist *sg, int nents,
	       enum dma_data_direction dir)
{
	int i;

	for (i = 0; i < nents; sg++, i++) {
		sg->dma_address = sg_phys(sg);
		dma_sync_single_for_device(dev, sg->dma_address, sg->length, dir);
	}
	return nents;
}
EXPORT_SYMBOL(dma_map_sg);
