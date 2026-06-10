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
#ifndef _IOMMU_COMMON_H
#define _IOMMU_COMMON_H

#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/sched.h>
#include <beep/mm.h>
#include <beep/scatterlist.h>
#include <beep/device.h>
#include <beep/iommu-helper.h>

#include <asm/iommu.h>
#include <asm/scatterlist.h>

/*
 * These give mapping size of each iommu pte/tlb.
 */
#define IO_PAGE_SHIFT			13
#define IO_PAGE_SIZE			(1UL << IO_PAGE_SHIFT)
#define IO_PAGE_MASK			(~(IO_PAGE_SIZE-1))
#define IO_PAGE_ALIGN(addr)		ALIGN(addr, IO_PAGE_SIZE)

#define IO_TSB_ENTRIES			(128*1024)
#define IO_TSB_SIZE			(IO_TSB_ENTRIES * 8)

/*
 * This is the hardwired shift in the iotlb tag/data parts.
 */
#define IOMMU_PAGE_SHIFT		13

#define SG_ENT_PHYS_ADDRESS(SG)	(__pa(sg_virt((SG))))

static inline int is_span_boundary(unsigned long entry,
				   unsigned long shift,
				   unsigned long boundary_size,
				   struct scatterlist *outs,
				   struct scatterlist *sg)
{
	unsigned long paddr = SG_ENT_PHYS_ADDRESS(outs);
	int nr = iommu_num_pages(paddr, outs->dma_length + sg->length,
				 IO_PAGE_SIZE);

	return iommu_is_span_boundary(entry, nr, shift, boundary_size);
}

extern unsigned long iommu_range_alloc(struct device *dev,
				       struct iommu *iommu,
				       unsigned long npages,
				       unsigned long *handle);
extern void iommu_range_free(struct iommu *iommu,
			     dma_addr_t dma_addr,
			     unsigned long npages);

#endif /* _IOMMU_COMMON_H */
