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
#ifndef _XTENSA_PCI_BRIDGE_H
#define _XTENSA_PCI_BRIDGE_H

#ifdef __KERNEL__

struct device_node;
struct pci_controller;

/*
 * pciauto_bus_scan() enumerates the pci space.
 */

extern int pciauto_bus_scan(struct pci_controller *, int);

struct pci_space {
	unsigned long start;
	unsigned long end;
	unsigned long base;
};

/*
 * Structure of a PCI controller (host bridge)
 */

struct pci_controller {
	int index;			/* used for pci_controller_num */
	struct pci_controller *next;
	struct pci_bus *bus;
	void *arch_data;

	int first_busno;
	int last_busno;

	struct pci_ops *ops;
	volatile unsigned int *cfg_addr;
	volatile unsigned char *cfg_data;

	/* Currently, we limit ourselves to 1 IO range and 3 mem
	 * ranges since the common pci_bus structure can't handle more
	 */
	struct resource	io_resource;
	struct resource mem_resources[3];
	int mem_resource_count;

	/* Host bridge I/O and Memory space
	 * Used for BAR placement algorithms
	 */
	struct pci_space io_space;
	struct pci_space mem_space;

	/* Return the interrupt number fo a device. */
	int (*map_irq)(struct pci_dev*, u8, u8);

};

static inline void pcibios_init_resource(struct resource *res,
		unsigned long start, unsigned long end, int flags, char *name)
{
	res->start = start;
	res->end = end;
	res->flags = flags;
	res->name = name;
	res->parent = NULL;
	res->sibling = NULL;
	res->child = NULL;
}


/* These are used for config access before all the PCI probing has been done. */
int early_read_config_byte(struct pci_controller*, int, int, int, u8*);
int early_read_config_word(struct pci_controller*, int, int, int, u16*);
int early_read_config_dword(struct pci_controller*, int, int, int, u32*);
int early_write_config_byte(struct pci_controller*, int, int, int, u8);
int early_write_config_word(struct pci_controller*, int, int, int, u16);
int early_write_config_dword(struct pci_controller*, int, int, int, u32);

#endif	/* __KERNEL__ */
#endif	/* _XTENSA_PCI_BRIDGE_H */
