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
#ifndef _ASM_PCI_H
#define _ASM_PCI_H

#include <beep/mm.h>

#ifdef __KERNEL__

/*
 * This file essentially defines the interface between board
 * specific PCI code and MIPS common PCI code.  Should potentially put
 * into include/asm/pci.h file.
 */

#include <beep/ioport.h>
#include <beep/of.h>

/*
 * Each pci channel is a top-level PCI bus seem by CPU.  A machine  with
 * multiple PCI channels may have multiple PCI host controllers or a
 * single controller supporting multiple channels.
 */
struct pci_controller {
	struct pci_controller *next;
	struct pci_bus *bus;
	struct device_node *of_node;

	struct pci_ops *pci_ops;
	struct resource *mem_resource;
	unsigned long mem_offset;
	struct resource *io_resource;
	unsigned long io_offset;
	unsigned long io_map_base;

	unsigned int index;
	/* For compatibility with current (as of July 2003) pciutils
	   and XFree86. Eventually will be removed. */
	unsigned int need_domain_info;

	int iommu;

	/* Optional access methods for reading/writing the bus number
	   of the PCI controller */
	int (*get_busno)(void);
	void (*set_busno)(int busno);
};

/*
 * Used by boards to register their PCI busses before the actual scanning.
 */
extern struct pci_controller * alloc_pci_controller(void);
extern void register_pci_controller(struct pci_controller *hose);

/*
 * board supplied pci irq fixup routine
 */
extern int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin);


/* Can be used to override the logic in pci_scan_bus for skipping
   already-configured bus numbers - to be used for buggy BIOSes
   or architectures with incomplete PCI setup by the loader */

extern unsigned int pcibios_assign_all_busses(void);

extern unsigned long PCIBIOS_MIN_IO;
extern unsigned long PCIBIOS_MIN_MEM;

#define PCIBIOS_MIN_CARDBUS_IO	0x4000

extern void pcibios_set_master(struct pci_dev *dev);

static inline void pcibios_penalize_isa_irq(int irq, int active)
{
	/* We don't do dynamic PCI IRQ allocation */
}

#define HAVE_PCI_MMAP

extern int pci_mmap_page_range(struct pci_dev *dev, struct vm_area_struct *vma,
	enum pci_mmap_state mmap_state, int write_combine);

/*
 * Dynamic DMA mapping stuff.
 * MIPS has everything mapped statically.
 */

#include <beep/types.h>
#include <beep/slab.h>
#include <asm/scatterlist.h>
#include <beep/string.h>
#include <asm/io.h>
#include <asm-generic/pci-bridge.h>

struct pci_dev;

/*
 * The PCI address space does equal the physical memory address space.  The
 * networking and block device layers use this boolean for bounce buffer
 * decisions.  This is set if any hose does not have an IOMMU.
 */
extern unsigned int PCI_DMA_BUS_IS_PHYS;

#ifdef CONFIG_PCI
static inline void pci_dma_burst_advice(struct pci_dev *pdev,
					enum pci_dma_burst_strategy *strat,
					unsigned long *strategy_parameter)
{
	*strat = PCI_DMA_BURST_INFINITY;
	*strategy_parameter = ~0UL;
}
#endif

#define pci_domain_nr(bus) ((struct pci_controller *)(bus)->sysdata)->index

static inline int pci_proc_domain(struct pci_bus *bus)
{
	struct pci_controller *hose = bus->sysdata;
	return hose->need_domain_info;
}

#endif /* __KERNEL__ */

/* implement the pci_ DMA API in terms of the generic device dma_ one */
#include <asm-generic/pci-dma-compat.h>

/* Do platform specific device initialization at pci_enable_device() time */
extern int pcibios_plat_dev_init(struct pci_dev *dev);

/* Chances are this interrupt is wired PC-style ...  */
static inline int pci_get_legacy_ide_irq(struct pci_dev *dev, int channel)
{
	return channel ? 15 : 14;
}

#ifdef CONFIG_CPU_CAVIUM_OCTEON
/* MSI arch hook for OCTEON */
#define arch_setup_msi_irqs arch_setup_msi_irqs
#endif

extern char * (*pcibios_plat_setup)(char *str);

/* this function parses memory ranges from a device node */
extern void pci_load_of_ranges(struct pci_controller *hose,
			       struct device_node *node);

#endif /* _ASM_PCI_H */
