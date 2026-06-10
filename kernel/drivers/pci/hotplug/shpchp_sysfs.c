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
#include "shpchp.h"


/* A few routines that create sysfs entries for the hot plug controller */

static ssize_t show_ctrl (struct device *dev, struct device_attribute *attr, char *buf)
{
	struct pci_dev *pdev;
	char * out = buf;
	int index, busnr;
	struct resource *res;
	struct pci_bus *bus;

	pdev = container_of (dev, struct pci_dev, dev);
	bus = pdev->subordinate;

	out += sprintf(buf, "Free resources: memory\n");
	pci_bus_for_each_resource(bus, res, index) {
		if (res && (res->flags & IORESOURCE_MEM) &&
				!(res->flags & IORESOURCE_PREFETCH)) {
			out += sprintf(out, "start = %8.8llx, length = %8.8llx\n",
				       (unsigned long long)res->start,
				       (unsigned long long)resource_size(res));
		}
	}
	out += sprintf(out, "Free resources: prefetchable memory\n");
	pci_bus_for_each_resource(bus, res, index) {
		if (res && (res->flags & IORESOURCE_MEM) &&
			       (res->flags & IORESOURCE_PREFETCH)) {
			out += sprintf(out, "start = %8.8llx, length = %8.8llx\n",
				       (unsigned long long)res->start,
				       (unsigned long long)resource_size(res));
		}
	}
	out += sprintf(out, "Free resources: IO\n");
	pci_bus_for_each_resource(bus, res, index) {
		if (res && (res->flags & IORESOURCE_IO)) {
			out += sprintf(out, "start = %8.8llx, length = %8.8llx\n",
				       (unsigned long long)res->start,
				       (unsigned long long)resource_size(res));
		}
	}
	out += sprintf(out, "Free resources: bus numbers\n");
	for (busnr = bus->busn_res.start; busnr <= bus->busn_res.end; busnr++) {
		if (!pci_find_bus(pci_domain_nr(bus), busnr))
			break;
	}
	if (busnr < bus->busn_res.end)
		out += sprintf(out, "start = %8.8x, length = %8.8x\n",
				busnr, (int)(bus->busn_res.end - busnr));

	return out - buf;
}
static DEVICE_ATTR (ctrl, S_IRUGO, show_ctrl, NULL);

int __must_check shpchp_create_ctrl_files (struct controller *ctrl)
{
	return device_create_file (&ctrl->pci_dev->dev, &dev_attr_ctrl);
}

void shpchp_remove_ctrl_files(struct controller *ctrl)
{
	device_remove_file(&ctrl->pci_dev->dev, &dev_attr_ctrl);
}
