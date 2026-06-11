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
/*
 * Cardbus handling has been re-written to be more of a PCI bridge thing,
 * and the PCI code basically does all the resource handling.
 *
 *		Linus, Jan 2000
 */


#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/pci.h>

#include <pcmcia/ss.h>


static void cardbus_config_irq_and_cls(struct pci_bus *bus, int irq)
{
	struct pci_dev *dev;

	list_for_each_entry(dev, &bus->devices, bus_list) {
		u8 irq_pin;

		/*
		 * Since there is only one interrupt available to
		 * CardBus devices, all devices downstream of this
		 * device must be using this IRQ.
		 */
		pci_read_config_byte(dev, PCI_INTERRUPT_PIN, &irq_pin);
		if (irq_pin) {
			dev->irq = irq;
			pci_write_config_byte(dev, PCI_INTERRUPT_LINE, dev->irq);
		}

		/*
		 * Some controllers transfer very slowly with 0 CLS.
		 * Configure it.  This may fail as CLS configuration
		 * is mandatory only for MWI.
		 */
		pci_set_cacheline_size(dev);

		if (dev->subordinate)
			cardbus_config_irq_and_cls(dev->subordinate, irq);
	}
}

/**
 * cb_alloc() - add CardBus device
 * @s:		the pcmcia_socket where the CardBus device is located
 *
 * cb_alloc() allocates the kernel data structures for a Cardbus device
 * and handles the lowest level PCI device setup issues.
 */
int __ref cb_alloc(struct pcmcia_socket *s)
{
	struct pci_bus *bus = s->cb_dev->subordinate;
	struct pci_dev *dev;
	unsigned int max, pass;

	s->functions = pci_scan_slot(bus, PCI_DEVFN(0, 0));
	pci_fixup_cardbus(bus);

	max = bus->busn_res.start;
	for (pass = 0; pass < 2; pass++)
		list_for_each_entry(dev, &bus->devices, bus_list)
			if (dev->hdr_type == PCI_HEADER_TYPE_BRIDGE ||
			    dev->hdr_type == PCI_HEADER_TYPE_CARDBUS)
				max = pci_scan_bridge(bus, dev, max, pass);

	/*
	 * Size all resources below the CardBus controller.
	 */
	pci_bus_size_bridges(bus);
	pci_bus_assign_resources(bus);
	cardbus_config_irq_and_cls(bus, s->pci_irq);

	/* socket specific tune function */
	if (s->tune_bridge)
		s->tune_bridge(s, bus);

	pci_enable_bridges(bus);
	pci_bus_add_devices(bus);

	return 0;
}

/**
 * cb_free() - remove CardBus device
 * @s:		the pcmcia_socket where the CardBus device was located
 *
 * cb_free() handles the lowest level PCI device cleanup.
 */
void cb_free(struct pcmcia_socket *s)
{
	struct pci_dev *bridge, *dev, *tmp;
	struct pci_bus *bus;

	bridge = s->cb_dev;
	if (!bridge)
		return;

	bus = bridge->subordinate;
	if (!bus)
		return;

	list_for_each_entry_safe(dev, tmp, &bus->devices, bus_list)
		pci_stop_and_remove_bus_device(dev);
}
