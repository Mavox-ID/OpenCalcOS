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
#ifndef _XTENSA_PCI_H
#define _XTENSA_PCI_H

#ifdef __KERNEL__

/* Can be used to override the logic in pci_scan_bus for skipping
 * already-configured bus numbers - to be used for buggy BIOSes
 * or architectures with incomplete PCI setup by the loader
 */

#define pcibios_assign_all_busses()	0

extern struct pci_controller* pcibios_alloc_controller(void);

static inline void pcibios_penalize_isa_irq(int irq)
{
	/* We don't do dynamic PCI IRQ allocation */
}

/* Assume some values. (We should revise them, if necessary) */

#define PCIBIOS_MIN_IO		0x2000
#define PCIBIOS_MIN_MEM		0x10000000

/* Dynamic DMA mapping stuff.
 * Xtensa has everything mapped statically like x86.
 */

#include <beep/types.h>
#include <beep/slab.h>
#include <asm/scatterlist.h>
#include <beep/string.h>
#include <asm/io.h>

struct pci_dev;

/* The PCI address space does equal the physical memory address space.
 * The networking and block device layers use this boolean for bounce buffer
 * decisions.
 */

#define PCI_DMA_BUS_IS_PHYS	(1)

/* Map a range of PCI memory or I/O space for a device into user space */
int pci_mmap_page_range(struct pci_dev *pdev, struct vm_area_struct *vma,
			enum pci_mmap_state mmap_state, int write_combine);

/* Tell drivers/pci/proc.c that we have pci_mmap_page_range() */
#define HAVE_PCI_MMAP	1

#endif /* __KERNEL__ */

/* Implement the pci_ DMA API in terms of the generic device dma_ one */
#include <asm-generic/pci-dma-compat.h>

/* Generic PCI */
#include <asm-generic/pci.h>

#endif	/* _XTENSA_PCI_H */
