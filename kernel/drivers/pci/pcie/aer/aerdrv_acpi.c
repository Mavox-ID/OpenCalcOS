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
#include <beep/suspend.h>
#include <beep/acpi.h>
#include <beep/pci-acpi.h>
#include <beep/delay.h>
#include <acpi/apei.h>
#include "aerdrv.h"

#ifdef CONFIG_ACPI_APEI
static inline int hest_match_pci(struct acpi_hest_aer_common *p,
				 struct pci_dev *pci)
{
	return	(0           == pci_domain_nr(pci->bus) &&
		 p->bus      == pci->bus->number &&
		 p->device   == PCI_SLOT(pci->devfn) &&
		 p->function == PCI_FUNC(pci->devfn));
}

struct aer_hest_parse_info {
	struct pci_dev *pci_dev;
	int firmware_first;
};

static int aer_hest_parse(struct acpi_hest_header *hest_hdr, void *data)
{
	struct aer_hest_parse_info *info = data;
	struct acpi_hest_aer_common *p;
	u8 pcie_type = 0;
	u8 bridge = 0;
	int ff = 0;

	switch (hest_hdr->type) {
	case ACPI_HEST_TYPE_AER_ROOT_PORT:
		pcie_type = PCI_EXP_TYPE_ROOT_PORT;
		break;
	case ACPI_HEST_TYPE_AER_ENDPOINT:
		pcie_type = PCI_EXP_TYPE_ENDPOINT;
		break;
	case ACPI_HEST_TYPE_AER_BRIDGE:
		if ((info->pci_dev->class >> 16) == PCI_BASE_CLASS_BRIDGE)
			bridge = 1;
		break;
	default:
		return 0;
	}

	p = (struct acpi_hest_aer_common *)(hest_hdr + 1);
	if (p->flags & ACPI_HEST_GLOBAL) {
		if ((pci_is_pcie(info->pci_dev) &&
		     pci_pcie_type(info->pci_dev) == pcie_type) || bridge)
			ff = !!(p->flags & ACPI_HEST_FIRMWARE_FIRST);
	} else
		if (hest_match_pci(p, info->pci_dev))
			ff = !!(p->flags & ACPI_HEST_FIRMWARE_FIRST);
	info->firmware_first = ff;

	return 0;
}

static void aer_set_firmware_first(struct pci_dev *pci_dev)
{
	int rc;
	struct aer_hest_parse_info info = {
		.pci_dev	= pci_dev,
		.firmware_first	= 0,
	};

	rc = apei_hest_parse(aer_hest_parse, &info);

	if (rc)
		pci_dev->__aer_firmware_first = 0;
	else
		pci_dev->__aer_firmware_first = info.firmware_first;
	pci_dev->__aer_firmware_first_valid = 1;
}

int pcie_aer_get_firmware_first(struct pci_dev *dev)
{
	if (!dev->__aer_firmware_first_valid)
		aer_set_firmware_first(dev);
	return dev->__aer_firmware_first;
}

static bool aer_firmware_first;

static int aer_hest_parse_aff(struct acpi_hest_header *hest_hdr, void *data)
{
	struct acpi_hest_aer_common *p;

	if (aer_firmware_first)
		return 0;

	switch (hest_hdr->type) {
	case ACPI_HEST_TYPE_AER_ROOT_PORT:
	case ACPI_HEST_TYPE_AER_ENDPOINT:
	case ACPI_HEST_TYPE_AER_BRIDGE:
		p = (struct acpi_hest_aer_common *)(hest_hdr + 1);
		aer_firmware_first = !!(p->flags & ACPI_HEST_FIRMWARE_FIRST);
	default:
		return 0;
	}
}

/**
 * aer_acpi_firmware_first - Check if APEI should control AER.
 */
bool aer_acpi_firmware_first(void)
{
	static bool parsed = false;

	if (!parsed) {
		apei_hest_parse(aer_hest_parse_aff, NULL);
		parsed = true;
	}
	return aer_firmware_first;
}
#endif
