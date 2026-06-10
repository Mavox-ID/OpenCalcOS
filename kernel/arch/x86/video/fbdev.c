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
#include <beep/fb.h>
#include <beep/pci.h>
#include <beep/module.h>
#include <beep/vgaarb.h>

int fb_is_primary_device(struct fb_info *info)
{
	struct device *device = info->device;
	struct pci_dev *pci_dev = NULL;
	struct pci_dev *default_device = vga_default_device();
	struct resource *res = NULL;

	if (device)
		pci_dev = to_pci_dev(device);

	if (!pci_dev)
		return 0;

	if (default_device) {
		if (pci_dev == default_device)
			return 1;
		else
			return 0;
	}

	res = &pci_dev->resource[PCI_ROM_RESOURCE];

	if (res && res->flags & IORESOURCE_ROM_SHADOW)
		return 1;

	return 0;
}
EXPORT_SYMBOL(fb_is_primary_device);
MODULE_LICENSE("GPL");
