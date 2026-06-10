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
#ifndef __ASM_ARCH_MEMORY_H
#define __ASM_ARCH_MEMORY_H

#include <mach/hardware.h>

/*
 * Physical SRAM offset.
 */
#define PLAT_PHYS_OFFSET		KS8695_SDRAM_PA

#ifndef __ASSEMBLY__

#ifdef CONFIG_PCI

/* PCI mappings */
#define __virt_to_bus(x)	((x) - PAGE_OFFSET + KS8695_PCIMEM_PA)
#define __bus_to_virt(x)	((x) - KS8695_PCIMEM_PA + PAGE_OFFSET)

/* Platform-bus mapping */
extern struct bus_type platform_bus_type;
#define is_lbus_device(dev)		(dev && dev->bus == &platform_bus_type)
#define __arch_dma_to_virt(dev, x)	({ (void *) (is_lbus_device(dev) ? \
					__phys_to_virt(x) : __bus_to_virt(x)); })
#define __arch_virt_to_dma(dev, x)	({ is_lbus_device(dev) ? \
					(dma_addr_t)__virt_to_phys((unsigned long)x) \
					: (dma_addr_t)__virt_to_bus(x); })
#define __arch_pfn_to_dma(dev, pfn)	\
	({ dma_addr_t __dma = __pfn_to_phys(pfn); \
	   if (!is_lbus_device(dev)) \
		__dma = __dma - PHYS_OFFSET + KS8695_PCIMEM_PA; \
	   __dma; })

#define __arch_dma_to_pfn(dev, x)	\
	({ dma_addr_t __dma = x;				\
	   if (!is_lbus_device(dev))				\
		__dma += PHYS_OFFSET - KS8695_PCIMEM_PA;	\
	   __phys_to_pfn(__dma);				\
	})

#endif

#endif

#endif
