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
#ifndef _ASM_MICROBLAZE_DMA_H
#define _ASM_MICROBLAZE_DMA_H

#ifndef CONFIG_MMU
/* we don't have dma address limit. define it as zero to be
 * unlimited. */
#define MAX_DMA_ADDRESS		(0)
#else
/* Virtual address corresponding to last available physical memory address.  */
#define MAX_DMA_ADDRESS (CONFIG_KERNEL_START + memory_size - 1)
#endif

#ifdef CONFIG_PCI
extern int isa_dma_bridge_buggy;
#else
#define isa_dma_bridge_buggy     (0)
#endif

#endif /* _ASM_MICROBLAZE_DMA_H */
