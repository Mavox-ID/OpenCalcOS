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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/pci.h>
#include "../pci.h"
#include "shpchp.h"

int __ref shpchp_configure_device(struct slot *p_slot)
{
	struct pci_dev *dev;
	struct controller *ctrl = p_slot->ctrl;
	struct pci_dev *bridge = ctrl->pci_dev;
	struct pci_bus *parent = bridge->subordinate;
	int num, fn;

	dev = pci_get_slot(parent, PCI_DEVFN(p_slot->device, 0));
	if (dev) {
		ctrl_err(ctrl, "Device %s already exists "
			 "at %04x:%02x:%02x, cannot hot-add\n", pci_name(dev),
			 pci_domain_nr(parent), p_slot->bus, p_slot->device);
		pci_dev_put(dev);
		return -EINVAL;
	}

	num = pci_scan_slot(parent, PCI_DEVFN(p_slot->device, 0));
	if (num == 0) {
		ctrl_err(ctrl, "No new device found\n");
		return -ENODEV;
	}

	for (fn = 0; fn < 8; fn++) {
		dev = pci_get_slot(parent, PCI_DEVFN(p_slot->device, fn));
		if (!dev)
			continue;
		if ((dev->hdr_type == PCI_HEADER_TYPE_BRIDGE) ||
		    (dev->hdr_type == PCI_HEADER_TYPE_CARDBUS))
			pci_hp_add_bridge(dev);
		pci_dev_put(dev);
	}

	pci_assign_unassigned_bridge_resources(bridge);

	for (fn = 0; fn < 8; fn++) {
		dev = pci_get_slot(parent, PCI_DEVFN(p_slot->device, fn));
		if (!dev)
			continue;
		pci_configure_slot(dev);
		pci_dev_put(dev);
	}

	pci_bus_add_devices(parent);

	return 0;
}

int shpchp_unconfigure_device(struct slot *p_slot)
{
	int rc = 0;
	int j;
	u8 bctl = 0;
	struct pci_bus *parent = p_slot->ctrl->pci_dev->subordinate;
	struct controller *ctrl = p_slot->ctrl;

	ctrl_dbg(ctrl, "%s: domain:bus:dev = %04x:%02x:%02x\n",
		 __func__, pci_domain_nr(parent), p_slot->bus, p_slot->device);

	for (j = 0; j < 8 ; j++) {
		struct pci_dev *temp = pci_get_slot(parent,
				(p_slot->device << 3) | j);
		if (!temp)
			continue;
		if (temp->hdr_type == PCI_HEADER_TYPE_BRIDGE) {
			pci_read_config_byte(temp, PCI_BRIDGE_CONTROL, &bctl);
			if (bctl & PCI_BRIDGE_CTL_VGA) {
				ctrl_err(ctrl,
					 "Cannot remove display device %s\n",
					 pci_name(temp));
				pci_dev_put(temp);
				rc = -EINVAL;
				break;
			}
		}
		pci_stop_and_remove_bus_device(temp);
		pci_dev_put(temp);
	}
	return rc;
}

