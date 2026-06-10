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
#ifndef _XTENSA_DMA_H
#define _XTENSA_DMA_H

#include <asm/io.h>		/* need byte IO */

/*
 * This is only to be defined if we have PC-like DMA.
 * By default this is not true on an Xtensa processor,
 * however on boards with a PCI bus, such functionality
 * might be emulated externally.
 *
 * NOTE:  there still exists driver code that assumes
 * this is defined, eg. drivers/sound/soundcard.c (as of 2.4).
 */
#define MAX_DMA_CHANNELS	8

/*
 * The maximum virtual address to which DMA transfers
 * can be performed on this platform.
 *
 * NOTE: This is board (platform) specific, not processor-specific!
 *
 * NOTE: This assumes DMA transfers can only be performed on
 *	the section of physical memory contiguously mapped in virtual
 *	space for the kernel.  For the Xtensa architecture, this
 *	means the maximum possible size of this DMA area is
 *	the size of the statically mapped kernel segment
 *	(XCHAL_KSEG_{CACHED,BYPASS}_SIZE), ie. 128 MB.
 *
 * NOTE: When the entire KSEG area is DMA capable, we subtract
 *	one from the max address so that the virt_to_phys() macro
 *	works correctly on the address (otherwise the address
 *	enters another area, and virt_to_phys() may not return
 *	the value desired).
 */

#ifndef MAX_DMA_ADDRESS
#define MAX_DMA_ADDRESS		(PAGE_OFFSET + XCHAL_KIO_SIZE - 1)
#endif

/* Reserve and release a DMA channel */
extern int request_dma(unsigned int dmanr, const char * device_id);
extern void free_dma(unsigned int dmanr);

#ifdef CONFIG_PCI
extern int isa_dma_bridge_buggy;
#else
#define isa_dma_bridge_buggy 	(0)
#endif


#endif
