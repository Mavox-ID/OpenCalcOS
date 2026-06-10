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
#include <beep/device.h>
#include <beep/dma-mapping.h>
#include <beep/swiotlb.h>
#include <beep/export.h>
#include <asm/machvec.h>

extern struct dma_map_ops sba_dma_ops, swiotlb_dma_ops;

/* swiotlb declarations & definitions: */
extern int swiotlb_late_init_with_default_size (size_t size);

/*
 * Note: we need to make the determination of whether or not to use
 * the sw I/O TLB based purely on the device structure.  Anything else
 * would be unreliable or would be too intrusive.
 */
static inline int use_swiotlb(struct device *dev)
{
	return dev && dev->dma_mask &&
		!sba_dma_ops.dma_supported(dev, *dev->dma_mask);
}

struct dma_map_ops *hwsw_dma_get_ops(struct device *dev)
{
	if (use_swiotlb(dev))
		return &swiotlb_dma_ops;
	return &sba_dma_ops;
}
EXPORT_SYMBOL(hwsw_dma_get_ops);

void __init
hwsw_init (void)
{
	/* default to a smallish 2MB sw I/O TLB */
	if (swiotlb_late_init_with_default_size (2 * (1<<20)) != 0) {
#ifdef CONFIG_IA64_GENERIC
		/* Better to have normal DMA than panic */
		printk(KERN_WARNING "%s: Failed to initialize software I/O TLB,"
		       " reverting to hpzx1 platform vector\n", __func__);
		machvec_init("hpzx1");
#else
		panic("Unable to initialize software I/O TLB services");
#endif
	}
}
