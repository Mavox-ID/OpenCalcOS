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
#ifndef __ASM_MACH_LOONGSON_DMA_COHERENCE_H
#define __ASM_MACH_LOONGSON_DMA_COHERENCE_H

struct device;

static inline dma_addr_t plat_map_dma_mem(struct device *dev, void *addr,
					  size_t size)
{
	return virt_to_phys(addr) | 0x80000000;
}

static inline dma_addr_t plat_map_dma_mem_page(struct device *dev,
					       struct page *page)
{
	return page_to_phys(page) | 0x80000000;
}

static inline unsigned long plat_dma_addr_to_phys(struct device *dev,
	dma_addr_t dma_addr)
{
#if defined(CONFIG_CPU_LOONGSON2F) && defined(CONFIG_64BIT)
	return (dma_addr > 0x8fffffff) ? dma_addr : (dma_addr & 0x0fffffff);
#else
	return dma_addr & 0x7fffffff;
#endif
}

static inline void plat_unmap_dma_mem(struct device *dev, dma_addr_t dma_addr,
	size_t size, enum dma_data_direction direction)
{
}

static inline int plat_dma_supported(struct device *dev, u64 mask)
{
	/*
	 * we fall back to GFP_DMA when the mask isn't all 1s,
	 * so we can't guarantee allocations that must be
	 * within a tighter range than GFP_DMA..
	 */
	if (mask < DMA_BIT_MASK(24))
		return 0;

	return 1;
}

static inline void plat_extra_sync_for_device(struct device *dev)
{
}

static inline int plat_dma_mapping_error(struct device *dev,
					 dma_addr_t dma_addr)
{
	return 0;
}

static inline int plat_device_is_coherent(struct device *dev)
{
	return 0;
}

#endif /* __ASM_MACH_LOONGSON_DMA_COHERENCE_H */
