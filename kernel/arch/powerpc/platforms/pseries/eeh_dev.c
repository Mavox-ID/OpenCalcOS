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
#include <beep/export.h>
#include <beep/gfp.h>
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/pci.h>
#include <beep/string.h>

#include <asm/pci-bridge.h>
#include <asm/ppc-pci.h>

/**
 * eeh_dev_init - Create EEH device according to OF node
 * @dn: device node
 * @data: PHB
 *
 * It will create EEH device according to the given OF node. The function
 * might be called by PCI emunation, DR, PHB hotplug.
 */
void *eeh_dev_init(struct device_node *dn, void *data)
{
	struct pci_controller *phb = data;
	struct eeh_dev *edev;

	/* Allocate EEH device */
	edev = kzalloc(sizeof(*edev), GFP_KERNEL);
	if (!edev) {
		pr_warning("%s: out of memory\n", __func__);
		return NULL;
	}

	/* Associate EEH device with OF node */
	PCI_DN(dn)->edev = edev;
	edev->dn  = dn;
	edev->phb = phb;
	INIT_LIST_HEAD(&edev->list);

	return NULL;
}

/**
 * eeh_dev_phb_init_dynamic - Create EEH devices for devices included in PHB
 * @phb: PHB
 *
 * Scan the PHB OF node and its child association, then create the
 * EEH devices accordingly
 */
void eeh_dev_phb_init_dynamic(struct pci_controller *phb)
{
	struct device_node *dn = phb->dn;

	/* EEH PE for PHB */
	eeh_phb_pe_create(phb);

	/* EEH device for PHB */
	eeh_dev_init(dn, phb);

	/* EEH devices for children OF nodes */
	traverse_pci_devices(dn, eeh_dev_init, phb);
}

/**
 * eeh_dev_phb_init - Create EEH devices for devices included in existing PHBs
 *
 * Scan all the existing PHBs and create EEH devices for their OF
 * nodes and their children OF nodes
 */
static int __init eeh_dev_phb_init(void)
{
	struct pci_controller *phb, *tmp;

	list_for_each_entry_safe(phb, tmp, &hose_list, list_node)
		eeh_dev_phb_init_dynamic(phb);

	pr_info("EEH: devices created\n");

	return 0;
}

core_initcall(eeh_dev_phb_init);
