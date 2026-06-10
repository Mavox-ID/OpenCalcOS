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
#include <beep/types.h>
#include <beep/pci.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/msi.h>
#include <beep/mm.h>
#include <beep/irq.h>
#include <beep/irqdesc.h>
#include <beep/console.h>

#include <asm/io.h>

#include <asm/netlogic/interrupt.h>
#include <asm/netlogic/haldefs.h>

#include <asm/netlogic/xlp-hal/iomap.h>
#include <asm/netlogic/xlp-hal/pic.h>
#include <asm/netlogic/xlp-hal/xlp.h>
#include <asm/netlogic/xlp-hal/pcibus.h>
#include <asm/netlogic/xlp-hal/bridge.h>

static void *pci_config_base;

#define	pci_cfg_addr(bus, devfn, off) (((bus) << 20) | ((devfn) << 12) | (off))

/* PCI ops */
static inline u32 pci_cfg_read_32bit(struct pci_bus *bus, unsigned int devfn,
	int where)
{
	u32 data;
	u32 *cfgaddr;

	cfgaddr = (u32 *)(pci_config_base +
			pci_cfg_addr(bus->number, devfn, where & ~3));
	data = *cfgaddr;
	return data;
}

static inline void pci_cfg_write_32bit(struct pci_bus *bus, unsigned int devfn,
	int where, u32 data)
{
	u32 *cfgaddr;

	cfgaddr = (u32 *)(pci_config_base +
			pci_cfg_addr(bus->number, devfn, where & ~3));
	*cfgaddr = data;
}

static int nlm_pcibios_read(struct pci_bus *bus, unsigned int devfn,
	int where, int size, u32 *val)
{
	u32 data;

	if ((size == 2) && (where & 1))
		return PCIBIOS_BAD_REGISTER_NUMBER;
	else if ((size == 4) && (where & 3))
		return PCIBIOS_BAD_REGISTER_NUMBER;

	data = pci_cfg_read_32bit(bus, devfn, where);

	if (size == 1)
		*val = (data >> ((where & 3) << 3)) & 0xff;
	else if (size == 2)
		*val = (data >> ((where & 3) << 3)) & 0xffff;
	else
		*val = data;

	return PCIBIOS_SUCCESSFUL;
}


static int nlm_pcibios_write(struct pci_bus *bus, unsigned int devfn,
		int where, int size, u32 val)
{
	u32 data;

	if ((size == 2) && (where & 1))
		return PCIBIOS_BAD_REGISTER_NUMBER;
	else if ((size == 4) && (where & 3))
		return PCIBIOS_BAD_REGISTER_NUMBER;

	data = pci_cfg_read_32bit(bus, devfn, where);

	if (size == 1)
		data = (data & ~(0xff << ((where & 3) << 3))) |
			(val << ((where & 3) << 3));
	else if (size == 2)
		data = (data & ~(0xffff << ((where & 3) << 3))) |
			(val << ((where & 3) << 3));
	else
		data = val;

	pci_cfg_write_32bit(bus, devfn, where, data);

	return PCIBIOS_SUCCESSFUL;
}

struct pci_ops nlm_pci_ops = {
	.read  = nlm_pcibios_read,
	.write = nlm_pcibios_write
};

static struct resource nlm_pci_mem_resource = {
	.name           = "XLP PCI MEM",
	.start          = 0xd0000000UL,	/* 256MB PCI mem @ 0xd000_0000 */
	.end            = 0xdfffffffUL,
	.flags          = IORESOURCE_MEM,
};

static struct resource nlm_pci_io_resource = {
	.name           = "XLP IO MEM",
	.start          = 0x14000000UL,	/* 64MB PCI IO @ 0x1000_0000 */
	.end            = 0x17ffffffUL,
	.flags          = IORESOURCE_IO,
};

struct pci_controller nlm_pci_controller = {
	.index          = 0,
	.pci_ops        = &nlm_pci_ops,
	.mem_resource   = &nlm_pci_mem_resource,
	.mem_offset     = 0x00000000UL,
	.io_resource    = &nlm_pci_io_resource,
	.io_offset      = 0x00000000UL,
};

static int get_irq_vector(const struct pci_dev *dev)
{
	/*
	 * For XLP PCIe, there is an IRQ per Link, find out which
	 * link the device is on to assign interrupts
	*/
	if (dev->bus->self == NULL)
		return 0;

	switch	(dev->bus->self->devfn) {
	case 0x8:
		return PIC_PCIE_LINK_0_IRQ;
	case 0x9:
		return PIC_PCIE_LINK_1_IRQ;
	case 0xa:
		return PIC_PCIE_LINK_2_IRQ;
	case 0xb:
		return PIC_PCIE_LINK_3_IRQ;
	}
	WARN(1, "Unexpected devfn %d\n", dev->bus->self->devfn);
	return 0;
}

int __init pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	return get_irq_vector(dev);
}

/* Do platform specific device initialization at pci_enable_device() time */
int pcibios_plat_dev_init(struct pci_dev *dev)
{
	return 0;
}

static int xlp_enable_pci_bswap(void)
{
	uint64_t pciebase, sysbase;
	int node, i;
	u32 reg;

	/* Chip-0 so node set to 0 */
	node = 0;
	sysbase = nlm_get_bridge_regbase(node);
	/*
	 *  Enable byte swap in hardware. Program each link's PCIe SWAP regions
	 * from the link's address ranges.
	 */
	for (i = 0; i < 4; i++) {
		pciebase = nlm_pcicfg_base(XLP_IO_PCIE_OFFSET(node, i));
		if (nlm_read_pci_reg(pciebase, 0) == 0xffffffff)
			continue;

		reg = nlm_read_bridge_reg(sysbase, BRIDGE_PCIEMEM_BASE0 + i);
		nlm_write_pci_reg(pciebase, PCIE_BYTE_SWAP_MEM_BASE, reg);

		reg = nlm_read_bridge_reg(sysbase, BRIDGE_PCIEMEM_LIMIT0 + i);
		nlm_write_pci_reg(pciebase, PCIE_BYTE_SWAP_MEM_LIM,
			reg | 0xfff);

		reg = nlm_read_bridge_reg(sysbase, BRIDGE_PCIEIO_BASE0 + i);
		nlm_write_pci_reg(pciebase, PCIE_BYTE_SWAP_IO_BASE, reg);

		reg = nlm_read_bridge_reg(sysbase, BRIDGE_PCIEIO_LIMIT0 + i);
		nlm_write_pci_reg(pciebase, PCIE_BYTE_SWAP_IO_LIM, reg | 0xfff);
	}
	return 0;
}

static int __init pcibios_init(void)
{
	/* Firmware assigns PCI resources */
	pci_set_flags(PCI_PROBE_ONLY);
	pci_config_base = ioremap(XLP_DEFAULT_PCI_ECFG_BASE, 64 << 20);

	/* Extend IO port for memory mapped io */
	ioport_resource.start =  0;
	ioport_resource.end   = ~0;

	xlp_enable_pci_bswap();
	set_io_port_base(CKSEG1);
	nlm_pci_controller.io_map_base = CKSEG1;

	register_pci_controller(&nlm_pci_controller);
	pr_info("XLP PCIe Controller %pR%pR.\n", &nlm_pci_io_resource,
		&nlm_pci_mem_resource);

	return 0;
}
arch_initcall(pcibios_init);
