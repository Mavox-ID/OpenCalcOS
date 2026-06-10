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
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/acpi.h>
#include <beep/pci-acpi.h>
#include <beep/pcieport_if.h>

#include "aer/aerdrv.h"
#include "../pci.h"

/**
 * pcie_port_acpi_setup - Request the BIOS to release control of PCIe services.
 * @port: PCIe Port service for a root port or event collector.
 * @srv_mask: Bit mask of services that can be enabled for @port.
 *
 * Invoked when @port is identified as a PCIe port device.  To avoid conflicts
 * with the BIOS PCIe port native services support requires the BIOS to yield
 * control of these services to the kernel.  The mask of services that the BIOS
 * allows to be enabled for @port is written to @srv_mask.
 *
 * NOTE: It turns out that we cannot do that for individual port services
 * separately, because that would make some systems work incorrectly.
 */
int pcie_port_acpi_setup(struct pci_dev *port, int *srv_mask)
{
	struct acpi_pci_root *root;
	acpi_handle handle;
	u32 flags;

	if (acpi_pci_disabled)
		return 0;

	handle = acpi_find_root_bridge_handle(port);
	if (!handle)
		return -EINVAL;

	root = acpi_pci_find_root(handle);
	if (!root)
		return -ENODEV;

	flags = root->osc_control_set;

	*srv_mask = PCIE_PORT_SERVICE_VC;
	if (flags & OSC_PCI_EXPRESS_NATIVE_HP_CONTROL)
		*srv_mask |= PCIE_PORT_SERVICE_HP;
	if (flags & OSC_PCI_EXPRESS_PME_CONTROL)
		*srv_mask |= PCIE_PORT_SERVICE_PME;
	if (flags & OSC_PCI_EXPRESS_AER_CONTROL)
		*srv_mask |= PCIE_PORT_SERVICE_AER;

	return 0;
}
