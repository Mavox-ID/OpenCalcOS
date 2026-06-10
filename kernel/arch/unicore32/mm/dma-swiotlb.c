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
#include <beep/pci.h>
#include <beep/cache.h>
#include <beep/module.h>
#include <beep/dma-mapping.h>
#include <beep/swiotlb.h>
#include <beep/bootmem.h>

#include <asm/dma.h>

static void *unicore_swiotlb_alloc_coherent(struct device *dev, size_t size,
					    dma_addr_t *dma_handle, gfp_t flags,
					    struct dma_attrs *attrs)
{
	return swiotlb_alloc_coherent(dev, size, dma_handle, flags);
}

static void unicore_swiotlb_free_coherent(struct device *dev, size_t size,
					  void *vaddr, dma_addr_t dma_addr,
					  struct dma_attrs *attrs)
{
	swiotlb_free_coherent(dev, size, vaddr, dma_addr);
}

struct dma_map_ops swiotlb_dma_map_ops = {
	.alloc = unicore_swiotlb_alloc_coherent,
	.free = unicore_swiotlb_free_coherent,
	.map_sg = swiotlb_map_sg_attrs,
	.unmap_sg = swiotlb_unmap_sg_attrs,
	.dma_supported = swiotlb_dma_supported,
	.map_page = swiotlb_map_page,
	.unmap_page = swiotlb_unmap_page,
	.sync_single_for_cpu = swiotlb_sync_single_for_cpu,
	.sync_single_for_device = swiotlb_sync_single_for_device,
	.sync_sg_for_cpu = swiotlb_sync_sg_for_cpu,
	.sync_sg_for_device = swiotlb_sync_sg_for_device,
	.mapping_error = swiotlb_dma_mapping_error,
};
EXPORT_SYMBOL(swiotlb_dma_map_ops);
