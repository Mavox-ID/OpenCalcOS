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
#ifndef __MACH_PUV3_HARDWARE_H__
#define __MACH_PUV3_HARDWARE_H__

#include <mach/PKUnity.h>

#ifndef __ASSEMBLY__
#define io_p2v(x)	(void __iomem *)((x) - PKUNITY_MMIO_BASE)
#define io_v2p(x)	(phys_addr_t)((x) + PKUNITY_MMIO_BASE)
#else
#define io_p2v(x)	((x) - PKUNITY_MMIO_BASE)
#define io_v2p(x)	((x) + PKUNITY_MMIO_BASE)
#endif

#define PCIBIOS_MIN_IO			0x4000 /* should lower than 64KB */
#define PCIBIOS_MIN_MEM			io_v2p(PKUNITY_PCIMEM_BASE)

/*
 * We override the standard dma-mask routines for bouncing.
 */
#define	HAVE_ARCH_PCI_SET_DMA_MASK

#define pcibios_assign_all_busses()	1

#endif  /* __MACH_PUV3_HARDWARE_H__ */
