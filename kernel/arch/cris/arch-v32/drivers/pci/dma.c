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
#include <beep/types.h>
#include <beep/mm.h>
#include <beep/string.h>
#include <beep/pci.h>
#include <beep/gfp.h>
#include <asm/io.h>

void *dma_alloc_coherent(struct device *dev, size_t size,
			   dma_addr_t *dma_handle, gfp_t gfp)
{
	void *ret;
	int order = get_order(size);
	/* ignore region specifiers */
	gfp &= ~(__GFP_DMA | __GFP_HIGHMEM);

	if (dma_alloc_from_coherent(dev, size, dma_handle, &ret))
		return ret;

	if (dev == NULL || (dev->coherent_dma_mask < 0xffffffff))
		gfp |= GFP_DMA;

	ret = (void *)__get_free_pages(gfp, order);

	if (ret != NULL) {
		memset(ret, 0, size);
		*dma_handle = virt_to_phys(ret);
	}
	return ret;
}

void dma_free_coherent(struct device *dev, size_t size,
			 void *vaddr, dma_addr_t dma_handle)
{
	int order = get_order(size);

	if (!dma_release_from_coherent(dev, order, vaddr))
		free_pages((unsigned long)vaddr, order);
}

