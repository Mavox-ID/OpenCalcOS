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
#ifndef _ASM_POWERPC_DEVICE_H
#define _ASM_POWERPC_DEVICE_H

struct dma_map_ops;
struct device_node;

/*
 * Arch extensions to struct device.
 *
 * When adding fields, consider macio_add_one_device in
 * drivers/macintosh/macio_asic.c
 */
struct dev_archdata {
	/* DMA operations on that device */
	struct dma_map_ops	*dma_ops;

	/*
	 * When an iommu is in use, dma_data is used as a ptr to the base of the
	 * iommu_table.  Otherwise, it is a simple numerical offset.
	 */
	union {
		dma_addr_t	dma_offset;
		void		*iommu_table_base;
	} dma_data;

#ifdef CONFIG_SWIOTLB
	dma_addr_t		max_direct_dma_addr;
#endif
#ifdef CONFIG_EEH
	struct eeh_dev		*edev;
#endif
#ifdef CONFIG_FAIL_IOMMU
	int fail_iommu;
#endif
};

struct pdev_archdata {
	u64 dma_mask;
};

#define ARCH_HAS_DMA_GET_REQUIRED_MASK

#endif /* _ASM_POWERPC_DEVICE_H */
