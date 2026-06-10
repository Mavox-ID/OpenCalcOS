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
#include <beep/module.h>
#include <beep/ssb/ssb.h>

#include "ssb_private.h"


static const struct pci_device_id b43_pci_bridge_tbl[] = {
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4301) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4306) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4307) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4311) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4312) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4315) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4318) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BCM_GVC,  0x4318) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4319) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4320) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4321) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4322) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 43222) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4324) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4325) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4328) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4329) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x432b) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x432c) },
	{ PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4350) },
	{ 0, },
};
MODULE_DEVICE_TABLE(pci, b43_pci_bridge_tbl);

static struct pci_driver b43_pci_bridge_driver = {
	.name = "b43-pci-bridge",
	.id_table = b43_pci_bridge_tbl,
};


int __init b43_pci_ssb_bridge_init(void)
{
	return ssb_pcihost_register(&b43_pci_bridge_driver);
}

void __exit b43_pci_ssb_bridge_exit(void)
{
	ssb_pcihost_unregister(&b43_pci_bridge_driver);
}
