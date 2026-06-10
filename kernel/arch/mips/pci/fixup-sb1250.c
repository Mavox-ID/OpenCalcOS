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
#include <beep/init.h>
#include <beep/pci.h>

/*
 * Set the BCM1250, etc. PCI host bridge's TRDY timeout
 * to the finite max.
 */
static void quirk_sb1250_pci(struct pci_dev *dev)
{
	pci_write_config_byte(dev, 0x40, 0xff);
}
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SIBYTE, PCI_DEVICE_ID_BCM1250_PCI,
			quirk_sb1250_pci);

/*
 * The BCM1250, etc. PCI/HT bridge reports as a host bridge.
 */
static void quirk_sb1250_ht(struct pci_dev *dev)
{
	dev->class = PCI_CLASS_BRIDGE_PCI << 8;
}
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SIBYTE, PCI_DEVICE_ID_BCM1250_HT,
			quirk_sb1250_ht);

/*
 * Set the SP1011 HT/PCI bridge's TRDY timeout to the finite max.
 */
static void quirk_sp1011(struct pci_dev *dev)
{
	pci_write_config_byte(dev, 0x64, 0xff);
}
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SIPACKETS, PCI_DEVICE_ID_SP1011,
			quirk_sp1011);
