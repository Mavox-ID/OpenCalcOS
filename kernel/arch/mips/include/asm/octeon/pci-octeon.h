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
#ifndef __PCI_OCTEON_H__
#define __PCI_OCTEON_H__

#include <beep/pci.h>

/* Some PCI cards require delays when accessing config space. */
#define PCI_CONFIG_SPACE_DELAY 10000

/*
 * The physical memory base mapped by BAR1.  256MB at the end of the
 * first 4GB.
 */
#define CVMX_PCIE_BAR1_PHYS_BASE ((1ull << 32) - (1ull << 28))
#define CVMX_PCIE_BAR1_PHYS_SIZE (1ull << 28)

/*
 * The RC base of BAR1.  gen1 has a 39-bit BAR2, gen2 has 41-bit BAR2,
 * place BAR1 so it is the same for both.
 */
#define CVMX_PCIE_BAR1_RC_BASE (1ull << 41)

/*
 * pcibios_map_irq() is defined inside pci-octeon.c. All it does is
 * call the Octeon specific version pointed to by this variable. This
 * function needs to change for PCI or PCIe based hosts.
 */
extern int (*octeon_pcibios_map_irq)(const struct pci_dev *dev,
				     u8 slot, u8 pin);

/*
 * For PCI (not PCIe) the BAR2 base address.
 */
#define OCTEON_BAR2_PCI_ADDRESS 0x8000000000ull

/*
 * For PCI (not PCIe) the base of the memory mapped by BAR1
 */
extern u64 octeon_bar1_pci_phys;

/*
 * The following defines are used when octeon_dma_bar_type =
 * OCTEON_DMA_BAR_TYPE_BIG
 */
#define OCTEON_PCI_BAR1_HOLE_BITS 5
#define OCTEON_PCI_BAR1_HOLE_SIZE (1ul<<(OCTEON_PCI_BAR1_HOLE_BITS+3))

enum octeon_dma_bar_type {
	OCTEON_DMA_BAR_TYPE_INVALID,
	OCTEON_DMA_BAR_TYPE_SMALL,
	OCTEON_DMA_BAR_TYPE_BIG,
	OCTEON_DMA_BAR_TYPE_PCIE,
	OCTEON_DMA_BAR_TYPE_PCIE2
};

/*
 * This tells the DMA mapping system in dma-octeon.c how to map PCI
 * DMA addresses.
 */
extern enum octeon_dma_bar_type octeon_dma_bar_type;

#endif
