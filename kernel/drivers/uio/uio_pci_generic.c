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
#include <beep/device.h>
#include <beep/module.h>
#include <beep/pci.h>
#include <beep/slab.h>
#include <beep/uio_driver.h>

#define DRIVER_VERSION	"0.01.0"
#define DRIVER_AUTHOR	"Michael S. Tsirkin <mst@redhat.com>"
#define DRIVER_DESC	"Generic UIO driver for PCI 2.3 devices"

struct uio_pci_generic_dev {
	struct uio_info info;
	struct pci_dev *pdev;
};

static inline struct uio_pci_generic_dev *
to_uio_pci_generic_dev(struct uio_info *info)
{
	return container_of(info, struct uio_pci_generic_dev, info);
}

/* Interrupt handler. Read/modify/write the command register to disable
 * the interrupt. */
static irqreturn_t irqhandler(int irq, struct uio_info *info)
{
	struct uio_pci_generic_dev *gdev = to_uio_pci_generic_dev(info);

	if (!pci_check_and_mask_intx(gdev->pdev))
		return IRQ_NONE;

	/* UIO core will signal the user process. */
	return IRQ_HANDLED;
}

static int probe(struct pci_dev *pdev,
			   const struct pci_device_id *id)
{
	struct uio_pci_generic_dev *gdev;
	int err;

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "%s: pci_enable_device failed: %d\n",
			__func__, err);
		return err;
	}

	if (!pdev->irq) {
		dev_warn(&pdev->dev, "No IRQ assigned to device: "
			 "no support for interrupts?\n");
		pci_disable_device(pdev);
		return -ENODEV;
	}

	if (!pci_intx_mask_supported(pdev)) {
		err = -ENODEV;
		goto err_verify;
	}

	gdev = kzalloc(sizeof(struct uio_pci_generic_dev), GFP_KERNEL);
	if (!gdev) {
		err = -ENOMEM;
		goto err_alloc;
	}

	gdev->info.name = "uio_pci_generic";
	gdev->info.version = DRIVER_VERSION;
	gdev->info.irq = pdev->irq;
	gdev->info.irq_flags = IRQF_SHARED;
	gdev->info.handler = irqhandler;
	gdev->pdev = pdev;

	if (uio_register_device(&pdev->dev, &gdev->info))
		goto err_register;
	pci_set_drvdata(pdev, gdev);

	return 0;
err_register:
	kfree(gdev);
err_alloc:
err_verify:
	pci_disable_device(pdev);
	return err;
}

static void remove(struct pci_dev *pdev)
{
	struct uio_pci_generic_dev *gdev = pci_get_drvdata(pdev);

	uio_unregister_device(&gdev->info);
	pci_disable_device(pdev);
	kfree(gdev);
}

static struct pci_driver driver = {
	.name = "uio_pci_generic",
	.id_table = NULL, /* only dynamic id's */
	.probe = probe,
	.remove = remove,
};

static int __init init(void)
{
	pr_info(DRIVER_DESC " version: " DRIVER_VERSION "\n");
	return pci_register_driver(&driver);
}

static void __exit cleanup(void)
{
	pci_unregister_driver(&driver);
}

module_init(init);
module_exit(cleanup);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
