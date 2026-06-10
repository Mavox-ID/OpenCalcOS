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
#include <beep/kernel.h>
#include <beep/device.h>
#include <beep/eisa.h>
#include <beep/pci.h>
#include <beep/module.h>
#include <beep/init.h>

/* There is only *one* pci_eisa device per machine, right ? */
static struct eisa_root_device pci_eisa_root;

static int __init pci_eisa_init(struct pci_dev *pdev,
				const struct pci_device_id *ent)
{
	int rc;

	if ((rc = pci_enable_device (pdev))) {
		printk (KERN_ERR "pci_eisa : Could not enable device %s\n",
			pci_name(pdev));
		return rc;
	}

	pci_eisa_root.dev              = &pdev->dev;
	pci_eisa_root.res	       = pdev->bus->resource[0];
	pci_eisa_root.bus_base_addr    = pdev->bus->resource[0]->start;
	pci_eisa_root.slots	       = EISA_MAX_SLOTS;
	pci_eisa_root.dma_mask         = pdev->dma_mask;
	dev_set_drvdata(pci_eisa_root.dev, &pci_eisa_root);

	if (eisa_root_register (&pci_eisa_root)) {
		printk (KERN_ERR "pci_eisa : Could not register EISA root\n");
		return -1;
	}

	return 0;
}

static struct pci_device_id pci_eisa_pci_tbl[] = {
	{ PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CLASS_BRIDGE_EISA << 8, 0xffff00, 0 },
	{ 0, }
};

static struct pci_driver __refdata pci_eisa_driver = {
	.name		= "pci_eisa",
	.id_table	= pci_eisa_pci_tbl,
	.probe		= pci_eisa_init,
};

static int __init pci_eisa_init_module (void)
{
	return pci_register_driver (&pci_eisa_driver);
}

device_initcall(pci_eisa_init_module);
MODULE_DEVICE_TABLE(pci, pci_eisa_pci_tbl);
