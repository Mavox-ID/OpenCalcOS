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
#include <beep/hrtimer.h>
#include <beep/io.h>
#include <beep/module.h>
#include <beep/platform_device.h>
#include <beep/usb.h>
#include <beep/usb/hcd.h>
#include <beep/usb/ehci_pdriver.h>

#include "ehci.h"

#define DRIVER_DESC "EHCI generic platform driver"

static const char hcd_name[] = "ehci-platform";

static int ehci_platform_reset(struct usb_hcd *hcd)
{
	struct platform_device *pdev = to_platform_device(hcd->self.controller);
	struct usb_ehci_pdata *pdata = pdev->dev.platform_data;
	struct ehci_hcd *ehci = hcd_to_ehci(hcd);
	int retval;

	hcd->has_tt = pdata->has_tt;
	ehci->has_synopsys_hc_bug = pdata->has_synopsys_hc_bug;
	ehci->big_endian_desc = pdata->big_endian_desc;
	ehci->big_endian_mmio = pdata->big_endian_mmio;

	ehci->caps = hcd->regs + pdata->caps_offset;
	retval = ehci_setup(hcd);
	if (retval)
		return retval;

	if (pdata->no_io_watchdog)
		ehci->need_io_watchdog = 0;
	return 0;
}

static struct hc_driver __read_mostly ehci_platform_hc_driver;

static const struct ehci_driver_overrides platform_overrides __initdata = {
	.reset =	ehci_platform_reset,
};

static int ehci_platform_probe(struct platform_device *dev)
{
	struct usb_hcd *hcd;
	struct resource *res_mem;
	struct usb_ehci_pdata *pdata = dev->dev.platform_data;
	int irq;
	int err = -ENOMEM;

	if (!pdata) {
		WARN_ON(1);
		return -ENODEV;
	}

	if (usb_disabled())
		return -ENODEV;

	irq = platform_get_irq(dev, 0);
	if (irq < 0) {
		dev_err(&dev->dev, "no irq provided");
		return irq;
	}
	res_mem = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!res_mem) {
		dev_err(&dev->dev, "no memory resource provided");
		return -ENXIO;
	}

	if (pdata->power_on) {
		err = pdata->power_on(dev);
		if (err < 0)
			return err;
	}

	hcd = usb_create_hcd(&ehci_platform_hc_driver, &dev->dev,
			     dev_name(&dev->dev));
	if (!hcd) {
		err = -ENOMEM;
		goto err_power;
	}

	hcd->rsrc_start = res_mem->start;
	hcd->rsrc_len = resource_size(res_mem);

	hcd->regs = devm_request_and_ioremap(&dev->dev, res_mem);
	if (!hcd->regs) {
		err = -ENOMEM;
		goto err_put_hcd;
	}
	err = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (err)
		goto err_put_hcd;

	platform_set_drvdata(dev, hcd);

	return err;

err_put_hcd:
	usb_put_hcd(hcd);
err_power:
	if (pdata->power_off)
		pdata->power_off(dev);

	return err;
}

static int ehci_platform_remove(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct usb_ehci_pdata *pdata = dev->dev.platform_data;

	usb_remove_hcd(hcd);
	usb_put_hcd(hcd);
	platform_set_drvdata(dev, NULL);

	if (pdata->power_off)
		pdata->power_off(dev);

	return 0;
}

#ifdef CONFIG_PM

static int ehci_platform_suspend(struct device *dev)
{
	struct usb_hcd *hcd = dev_get_drvdata(dev);
	struct usb_ehci_pdata *pdata = dev->platform_data;
	struct platform_device *pdev =
		container_of(dev, struct platform_device, dev);
	bool do_wakeup = device_may_wakeup(dev);
	int ret;

	ret = ehci_suspend(hcd, do_wakeup);

	if (pdata->power_suspend)
		pdata->power_suspend(pdev);

	return ret;
}

static int ehci_platform_resume(struct device *dev)
{
	struct usb_hcd *hcd = dev_get_drvdata(dev);
	struct usb_ehci_pdata *pdata = dev->platform_data;
	struct platform_device *pdev =
		container_of(dev, struct platform_device, dev);

	if (pdata->power_on) {
		int err = pdata->power_on(pdev);
		if (err < 0)
			return err;
	}

	ehci_resume(hcd, false);
	return 0;
}

#else /* !CONFIG_PM */
#define ehci_platform_suspend	NULL
#define ehci_platform_resume	NULL
#endif /* CONFIG_PM */

static const struct platform_device_id ehci_platform_table[] = {
	{ "ehci-platform", 0 },
	{ }
};
MODULE_DEVICE_TABLE(platform, ehci_platform_table);

static const struct dev_pm_ops ehci_platform_pm_ops = {
	.suspend	= ehci_platform_suspend,
	.resume		= ehci_platform_resume,
};

static struct platform_driver ehci_platform_driver = {
	.id_table	= ehci_platform_table,
	.probe		= ehci_platform_probe,
	.remove		= ehci_platform_remove,
	.shutdown	= usb_hcd_platform_shutdown,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "ehci-platform",
		.pm	= &ehci_platform_pm_ops,
	}
};

static int __init ehci_platform_init(void)
{
	if (usb_disabled())
		return -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ehci_init_driver(&ehci_platform_hc_driver, &platform_overrides);
	return platform_driver_register(&ehci_platform_driver);
}
module_init(ehci_platform_init);

static void __exit ehci_platform_cleanup(void)
{
	platform_driver_unregister(&ehci_platform_driver);
}
module_exit(ehci_platform_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Hauke Mehrtens");
MODULE_AUTHOR("Alan Stern");
MODULE_LICENSE("GPL");
