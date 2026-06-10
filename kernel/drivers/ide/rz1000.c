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
/*
 *  Principal Author:  mlord@pobox.com (Mark Lord)
 *
 *  See beep/MAINTAINERS for address of current maintainer.
 *
 *  This file provides support for disabling the buggy read-ahead
 *  mode of the RZ1000 IDE chipset, commonly used on Intel motherboards.
 *
 *  Dunno if this fixes both ports, or only the primary port (?).
 */

#include <beep/types.h>
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/pci.h>
#include <beep/ide.h>
#include <beep/init.h>

#define DRV_NAME "rz1000"

static int rz1000_disable_readahead(struct pci_dev *dev)
{
	u16 reg;

	if (!pci_read_config_word (dev, 0x40, &reg) &&
	    !pci_write_config_word(dev, 0x40, reg & 0xdfff)) {
		printk(KERN_INFO "%s: disabled chipset read-ahead "
			"(buggy RZ1000/RZ1001)\n", pci_name(dev));
		return 0;
	} else {
		printk(KERN_INFO "%s: serialized, disabled unmasking "
			"(buggy RZ1000/RZ1001)\n", pci_name(dev));
		return 1;
	}
}

static const struct ide_port_info rz1000_chipset = {
	.name		= DRV_NAME,
	.host_flags	= IDE_HFLAG_NO_DMA,
};

static int rz1000_init_one(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct ide_port_info d = rz1000_chipset;
	int rc;

	rc = pci_enable_device(dev);
	if (rc)
		return rc;

	if (rz1000_disable_readahead(dev)) {
		d.host_flags |= IDE_HFLAG_SERIALIZE;
		d.host_flags |= IDE_HFLAG_NO_UNMASK_IRQS;
	}

	return ide_pci_init_one(dev, &d, NULL);
}

static void rz1000_remove(struct pci_dev *dev)
{
	ide_pci_remove(dev);
	pci_disable_device(dev);
}

static const struct pci_device_id rz1000_pci_tbl[] = {
	{ PCI_VDEVICE(PCTECH, PCI_DEVICE_ID_PCTECH_RZ1000), 0 },
	{ PCI_VDEVICE(PCTECH, PCI_DEVICE_ID_PCTECH_RZ1001), 0 },
	{ 0, },
};
MODULE_DEVICE_TABLE(pci, rz1000_pci_tbl);

static struct pci_driver rz1000_pci_driver = {
	.name		= "RZ1000_IDE",
	.id_table	= rz1000_pci_tbl,
	.probe		= rz1000_init_one,
	.remove		= rz1000_remove,
};

static int __init rz1000_ide_init(void)
{
	return ide_pci_register_driver(&rz1000_pci_driver);
}

static void __exit rz1000_ide_exit(void)
{
	pci_unregister_driver(&rz1000_pci_driver);
}

module_init(rz1000_ide_init);
module_exit(rz1000_ide_exit);

MODULE_AUTHOR("Andre Hedrick");
MODULE_DESCRIPTION("PCI driver module for RZ1000 IDE");
MODULE_LICENSE("GPL");

