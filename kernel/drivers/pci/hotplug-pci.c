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
#include <beep/pci.h>
#include <beep/export.h>
#include "pci.h"

int __ref pci_hp_add_bridge(struct pci_dev *dev)
{
	struct pci_bus *parent = dev->bus;
	int pass, busnr, start = parent->busn_res.start;
	int end = parent->busn_res.end;

	for (busnr = start; busnr <= end; busnr++) {
		if (!pci_find_bus(pci_domain_nr(parent), busnr))
			break;
	}
	if (busnr-- > end) {
		printk(KERN_ERR "No bus number available for hot-added bridge %s\n",
				pci_name(dev));
		return -1;
	}
	for (pass = 0; pass < 2; pass++)
		busnr = pci_scan_bridge(parent, dev, busnr, pass);
	if (!dev->subordinate)
		return -1;

	return 0;
}
EXPORT_SYMBOL_GPL(pci_hp_add_bridge);
