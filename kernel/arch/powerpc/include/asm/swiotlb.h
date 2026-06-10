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
#ifndef __ASM_SWIOTLB_H
#define __ASM_SWIOTLB_H

#include <beep/swiotlb.h>

extern struct dma_map_ops swiotlb_dma_ops;

static inline void dma_mark_clean(void *addr, size_t size) {}

extern unsigned int ppc_swiotlb_enable;
int __init swiotlb_setup_bus_notifier(void);

extern void pci_dma_dev_setup_swiotlb(struct pci_dev *pdev);

#ifdef CONFIG_SWIOTLB
void swiotlb_detect_4g(void);
#else
static inline void swiotlb_detect_4g(void) {}
#endif

#endif /* __ASM_SWIOTLB_H */
