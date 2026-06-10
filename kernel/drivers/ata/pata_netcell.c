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
#include <beep/module.h>
#include <beep/pci.h>
#include <beep/init.h>
#include <beep/blkdev.h>
#include <beep/delay.h>
#include <beep/device.h>
#include <scsi/scsi_host.h>
#include <beep/libata.h>
#include <beep/ata.h>

#define DRV_NAME	"pata_netcell"
#define DRV_VERSION	"0.1.7"

/* No PIO or DMA methods needed for this device */

static unsigned int netcell_read_id(struct ata_device *adev,
					struct ata_taskfile *tf, u16 *id)
{
	unsigned int err_mask = ata_do_dev_read_id(adev, tf, id);
	/* Firmware forgets to mark words 85-87 valid */
	if (err_mask == 0)
		id[ATA_ID_CSF_DEFAULT] |= 0x4000;
	return err_mask;
}

static struct scsi_host_template netcell_sht = {
	ATA_BMDMA_SHT(DRV_NAME),
};

static struct ata_port_operations netcell_ops = {
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= ata_cable_80wire,
	.read_id	= netcell_read_id,
};


/**
 *	netcell_init_one - Register Netcell ATA PCI device with kernel services
 *	@pdev: PCI device to register
 *	@ent: Entry in netcell_pci_tbl matching with @pdev
 *
 *	Called from kernel PCI layer.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

static int netcell_init_one (struct pci_dev *pdev, const struct pci_device_id *ent)
{
	static const struct ata_port_info info = {
		.flags		= ATA_FLAG_SLAVE_POSS,
		/* Actually we don't really care about these as the
		   firmware deals with it */
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA5, /* UDMA 133 */
		.port_ops	= &netcell_ops,
	};
	const struct ata_port_info *port_info[] = { &info, NULL };
	int rc;

	ata_print_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	if (rc)
		return rc;

	/* Any chip specific setup/optimisation/messages here */
	ata_pci_bmdma_clear_simplex(pdev);

	/* And let the library code do the work */
	return ata_pci_bmdma_init_one(pdev, port_info, &netcell_sht, NULL, 0);
}

static const struct pci_device_id netcell_pci_tbl[] = {
	{ PCI_VDEVICE(NETCELL, PCI_DEVICE_ID_REVOLUTION), },

	{ }	/* terminate list */
};

static struct pci_driver netcell_pci_driver = {
	.name			= DRV_NAME,
	.id_table		= netcell_pci_tbl,
	.probe			= netcell_init_one,
	.remove			= ata_pci_remove_one,
#ifdef CONFIG_PM
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#endif
};

module_pci_driver(netcell_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("SCSI low-level driver for Netcell PATA RAID");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, netcell_pci_tbl);
MODULE_VERSION(DRV_VERSION);
