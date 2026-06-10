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
#include "rtl_pci.h"
#include "rtl_core.h"

static void rtl8192_parse_pci_configuration(struct pci_dev *pdev,
					    struct net_device *dev)
{
	struct r8192_priv *priv = (struct r8192_priv *)rtllib_priv(dev);

	u8 tmp;
	u16 LinkCtrlReg;

	pcie_capability_read_word(priv->pdev, PCI_EXP_LNKCTL, &LinkCtrlReg);
	priv->NdisAdapter.LinkCtrlReg = (u8)LinkCtrlReg;

	RT_TRACE(COMP_INIT, "Link Control Register =%x\n",
		 priv->NdisAdapter.LinkCtrlReg);

	pci_read_config_byte(pdev, 0x98, &tmp);
	tmp |= BIT4;
	pci_write_config_byte(pdev, 0x98, tmp);

	tmp = 0x17;
	pci_write_config_byte(pdev, 0x70f, tmp);
}

bool rtl8192_pci_findadapter(struct pci_dev *pdev, struct net_device *dev)
{
	struct r8192_priv *priv = (struct r8192_priv *)rtllib_priv(dev);
	u16 VenderID;
	u16 DeviceID;
	u8  RevisionID;
	u16 IrqLine;

	VenderID = pdev->vendor;
	DeviceID = pdev->device;
	RevisionID = pdev->revision;
	pci_read_config_word(pdev, 0x3C, &IrqLine);

	priv->card_8192 = priv->ops->nic_type;

	if (DeviceID == 0x8172) {
		switch (RevisionID) {
		case HAL_HW_PCI_REVISION_ID_8192PCIE:
			printk(KERN_INFO "Adapter(8192 PCI-E) is found - "
			       "DeviceID=%x\n", DeviceID);
			priv->card_8192 = NIC_8192E;
			break;
		case HAL_HW_PCI_REVISION_ID_8192SE:
			printk(KERN_INFO "Adapter(8192SE) is found - "
			       "DeviceID=%x\n", DeviceID);
			priv->card_8192 = NIC_8192SE;
			break;
		default:
			printk(KERN_INFO "UNKNOWN nic type(%4x:%4x)\n",
			       pdev->vendor, pdev->device);
			priv->card_8192 = NIC_UNKNOWN;
			return false;
		}
	}

	if (priv->ops->nic_type != priv->card_8192) {
		printk(KERN_INFO "Detect info(%x) and hardware info(%x) not match!\n",
				priv->ops->nic_type, priv->card_8192);
		printk(KERN_INFO "Please select proper driver before install!!!!\n");
		return false;
	}

	rtl8192_parse_pci_configuration(pdev, dev);

	return true;
}
