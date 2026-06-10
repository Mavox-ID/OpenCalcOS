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
#ifndef __ASM_MACH_CAVIUM_OCTEON_DMA_COHERENCE_H
#define __ASM_MACH_CAVIUM_OCTEON_DMA_COHERENCE_H

struct device;

extern void octeon_pci_dma_init(void);

static inline dma_addr_t plat_map_dma_mem(struct device *dev, void *addr,
	size_t size)
{
	BUG();
}

static inline dma_addr_t plat_map_dma_mem_page(struct device *dev,
	struct page *page)
{
	BUG();
}

static inline unsigned long plat_dma_addr_to_phys(struct device *dev,
	dma_addr_t dma_addr)
{
	BUG();
}

static inline void plat_unmap_dma_mem(struct device *dev, dma_addr_t dma_addr,
	size_t size, enum dma_data_direction direction)
{
	BUG();
}

static inline int plat_dma_supported(struct device *dev, u64 mask)
{
	BUG();
}

static inline void plat_extra_sync_for_device(struct device *dev)
{
	BUG();
}

static inline int plat_device_is_coherent(struct device *dev)
{
	return 1;
}

static inline int plat_dma_mapping_error(struct device *dev,
					 dma_addr_t dma_addr)
{
	BUG();
}

dma_addr_t phys_to_dma(struct device *dev, phys_addr_t paddr);
phys_addr_t dma_to_phys(struct device *dev, dma_addr_t daddr);

struct dma_map_ops;
extern struct dma_map_ops *octeon_pci_dma_map_ops;
extern char *octeon_swiotlb;

#endif /* __ASM_MACH_CAVIUM_OCTEON_DMA_COHERENCE_H */
