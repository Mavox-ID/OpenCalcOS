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
#include <beep/pci.h>
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/pm.h>

#include <beep/pcieport_if.h>
#include "portdrv.h"

static int pcie_port_bus_match(struct device *dev, struct device_driver *drv);

struct bus_type pcie_port_bus_type = {
	.name 		= "pci_express",
	.match 		= pcie_port_bus_match,
};
EXPORT_SYMBOL_GPL(pcie_port_bus_type);

static int pcie_port_bus_match(struct device *dev, struct device_driver *drv)
{
	struct pcie_device *pciedev;
	struct pcie_port_service_driver *driver;

	if (drv->bus != &pcie_port_bus_type || dev->bus != &pcie_port_bus_type)
		return 0;

	pciedev = to_pcie_device(dev);
	driver = to_service_driver(drv);

	if (driver->service != pciedev->service)
		return 0;

	if ((driver->port_type != PCIE_ANY_PORT) &&
	    (driver->port_type != pci_pcie_type(pciedev->port)))
		return 0;

	return 1;
}

int pcie_port_bus_register(void)
{
	return bus_register(&pcie_port_bus_type);
}

void pcie_port_bus_unregister(void)
{
	bus_unregister(&pcie_port_bus_type);
}
