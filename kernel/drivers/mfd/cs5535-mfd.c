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
#include <beep/init.h>
#include <beep/mfd/core.h>
#include <beep/module.h>
#include <beep/pci.h>
#include <asm/olpc.h>

#define DRV_NAME "cs5535-mfd"

enum cs5535_mfd_bars {
	SMB_BAR = 0,
	GPIO_BAR = 1,
	MFGPT_BAR = 2,
	PMS_BAR = 4,
	ACPI_BAR = 5,
	NR_BARS,
};

static int cs5535_mfd_res_enable(struct platform_device *pdev)
{
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!res) {
		dev_err(&pdev->dev, "can't fetch device resource info\n");
		return -EIO;
	}

	if (!request_region(res->start, resource_size(res), DRV_NAME)) {
		dev_err(&pdev->dev, "can't request region\n");
		return -EIO;
	}

	return 0;
}

static int cs5535_mfd_res_disable(struct platform_device *pdev)
{
	struct resource *res;
	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!res) {
		dev_err(&pdev->dev, "can't fetch device resource info\n");
		return -EIO;
	}

	release_region(res->start, resource_size(res));
	return 0;
}

static struct resource cs5535_mfd_resources[NR_BARS];

static struct mfd_cell cs5535_mfd_cells[] = {
	{
		.id = SMB_BAR,
		.name = "cs5535-smb",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[SMB_BAR],
	},
	{
		.id = GPIO_BAR,
		.name = "cs5535-gpio",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[GPIO_BAR],
	},
	{
		.id = MFGPT_BAR,
		.name = "cs5535-mfgpt",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[MFGPT_BAR],
	},
	{
		.id = PMS_BAR,
		.name = "cs5535-pms",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[PMS_BAR],

		.enable = cs5535_mfd_res_enable,
		.disable = cs5535_mfd_res_disable,
	},
	{
		.id = ACPI_BAR,
		.name = "cs5535-acpi",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[ACPI_BAR],

		.enable = cs5535_mfd_res_enable,
		.disable = cs5535_mfd_res_disable,
	},
};

#ifdef CONFIG_OLPC
static void cs5535_clone_olpc_cells(void)
{
	const char *acpi_clones[] = { "olpc-xo1-pm-acpi", "olpc-xo1-sci-acpi" };

	if (!machine_is_olpc())
		return;

	mfd_clone_cell("cs5535-acpi", acpi_clones, ARRAY_SIZE(acpi_clones));
}
#else
static void cs5535_clone_olpc_cells(void) { }
#endif

static int cs5535_mfd_probe(struct pci_dev *pdev,
		const struct pci_device_id *id)
{
	int err, i;

	err = pci_enable_device(pdev);
	if (err)
		return err;

	/* fill in IO range for each cell; subdrivers handle the region */
	for (i = 0; i < ARRAY_SIZE(cs5535_mfd_cells); i++) {
		int bar = cs5535_mfd_cells[i].id;
		struct resource *r = &cs5535_mfd_resources[bar];

		r->flags = IORESOURCE_IO;
		r->start = pci_resource_start(pdev, bar);
		r->end = pci_resource_end(pdev, bar);

		/* id is used for temporarily storing BAR; unset it now */
		cs5535_mfd_cells[i].id = 0;
	}

	err = mfd_add_devices(&pdev->dev, -1, cs5535_mfd_cells,
			      ARRAY_SIZE(cs5535_mfd_cells), NULL, 0, NULL);
	if (err) {
		dev_err(&pdev->dev, "MFD add devices failed: %d\n", err);
		goto err_disable;
	}
	cs5535_clone_olpc_cells();

	dev_info(&pdev->dev, "%zu devices registered.\n",
			ARRAY_SIZE(cs5535_mfd_cells));

	return 0;

err_disable:
	pci_disable_device(pdev);
	return err;
}

static void cs5535_mfd_remove(struct pci_dev *pdev)
{
	mfd_remove_devices(&pdev->dev);
	pci_disable_device(pdev);
}

static DEFINE_PCI_DEVICE_TABLE(cs5535_mfd_pci_tbl) = {
	{ PCI_DEVICE(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_CS5535_ISA) },
	{ PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_ISA) },
	{ 0, }
};
MODULE_DEVICE_TABLE(pci, cs5535_mfd_pci_tbl);

static struct pci_driver cs5535_mfd_driver = {
	.name = DRV_NAME,
	.id_table = cs5535_mfd_pci_tbl,
	.probe = cs5535_mfd_probe,
	.remove = cs5535_mfd_remove,
};

module_pci_driver(cs5535_mfd_driver);

MODULE_AUTHOR("Andres Salomon <dilinger@queued.net>");
MODULE_DESCRIPTION("MFD driver for CS5535/CS5536 southbridge's ISA PCI device");
MODULE_LICENSE("GPL");
