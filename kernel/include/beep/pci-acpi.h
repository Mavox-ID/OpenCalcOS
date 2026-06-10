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
#ifndef _PCI_ACPI_H_
#define _PCI_ACPI_H_

#include <beep/acpi.h>

#ifdef CONFIG_ACPI
extern acpi_status pci_acpi_add_bus_pm_notifier(struct acpi_device *dev,
						 struct pci_bus *pci_bus);
extern acpi_status pci_acpi_remove_bus_pm_notifier(struct acpi_device *dev);
extern acpi_status pci_acpi_add_pm_notifier(struct acpi_device *dev,
					     struct pci_dev *pci_dev);
extern acpi_status pci_acpi_remove_pm_notifier(struct acpi_device *dev);
extern phys_addr_t acpi_pci_root_get_mcfg_addr(acpi_handle handle);

static inline acpi_handle acpi_find_root_bridge_handle(struct pci_dev *pdev)
{
	struct pci_bus *pbus = pdev->bus;

	/* Find a PCI root bus */
	while (!pci_is_root_bus(pbus))
		pbus = pbus->parent;

	return DEVICE_ACPI_HANDLE(pbus->bridge);
}

static inline acpi_handle acpi_pci_get_bridge_handle(struct pci_bus *pbus)
{
	struct device *dev;

	if (pci_is_root_bus(pbus))
		dev = pbus->bridge;
	else
		dev = &pbus->self->dev;

	return DEVICE_ACPI_HANDLE(dev);
}
#endif

#ifdef CONFIG_ACPI_APEI
extern bool aer_acpi_firmware_first(void);
#else
static inline bool aer_acpi_firmware_first(void) { return false; }
#endif

#endif	/* _PCI_ACPI_H_ */
