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
#ifndef _PCI_ASB2305_H
#define _PCI_ASB2305_H

#undef DEBUG

#ifdef DEBUG
#define DBG(x...) printk(x)
#else
#define DBG(x...)
#endif

#define PCI_PROBE_BIOS 1
#define PCI_PROBE_CONF1 2
#define PCI_PROBE_CONF2 4
#define PCI_NO_CHECKS 0x400
#define PCI_ASSIGN_ROMS 0x1000
#define PCI_BIOS_IRQ_SCAN 0x2000

extern unsigned int pci_probe;

/* pci-asb2305.c */

extern void pcibios_resource_survey(void);

/* pci.c */

extern int pcibios_last_bus;
extern struct pci_bus *pci_root_bus;
extern struct pci_ops *pci_root_ops;

extern struct irq_routing_table *pcibios_get_irq_routing_table(void);
extern int pcibios_set_irq_routing(struct pci_dev *dev, int pin, int irq);

/* pci-irq.c */

struct irq_info {
	u8 bus, devfn;			/* Bus, device and function */
	struct {
		u8 link;		/* IRQ line ID, chipset dependent,
					 * 0=not routed */
		u16 bitmap;		/* Available IRQs */
	} __attribute__((packed)) irq[4];
	u8 slot;			/* Slot number, 0=onboard */
	u8 rfu;
} __attribute__((packed));

struct irq_routing_table {
	u32 signature;			/* PIRQ_SIGNATURE should be here */
	u16 version;			/* PIRQ_VERSION */
	u16 size;			/* Table size in bytes */
	u8 rtr_bus, rtr_devfn;		/* Where the interrupt router lies */
	u16 exclusive_irqs;		/* IRQs devoted exclusively to PCI usage */
	u16 rtr_vendor, rtr_device;	/* Vendor and device ID of interrupt router */
	u32 miniport_data;		/* Crap */
	u8 rfu[11];
	u8 checksum;			/* Modulo 256 checksum must give zero */
	struct irq_info slots[0];
} __attribute__((packed));

extern unsigned int pcibios_irq_mask;

extern void pcibios_irq_init(void);
extern void pcibios_fixup_irqs(void);
extern void pcibios_enable_irq(struct pci_dev *dev);

#endif /* PCI_ASB2305_H */
