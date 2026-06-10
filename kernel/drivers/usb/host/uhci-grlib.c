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
#include <beep/of_irq.h>
#include <beep/of_address.h>
#include <beep/of_platform.h>

static int uhci_grlib_init(struct usb_hcd *hcd)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);

	/*
	 * Probe to determine the endianness of the controller.
	 * We know that bit 7 of the PORTSC1 register is always set
	 * and bit 15 is always clear.  If uhci_readw() yields a value
	 * with bit 7 (0x80) turned on then the current little-endian
	 * setting is correct.  Otherwise we assume the value was
	 * byte-swapped; hence the register interface and presumably
	 * also the descriptors are big-endian.
	 */
	if (!(uhci_readw(uhci, USBPORTSC1) & 0x80)) {
		uhci->big_endian_mmio = 1;
		uhci->big_endian_desc = 1;
	}

	uhci->rh_numports = uhci_count_ports(hcd);

	/* Set up pointers to to generic functions */
	uhci->reset_hc = uhci_generic_reset_hc;
	uhci->check_and_reset_hc = uhci_generic_check_and_reset_hc;
	/* No special actions need to be taken for the functions below */
	uhci->configure_hc = NULL;
	uhci->resume_detect_interrupts_are_broken = NULL;
	uhci->global_suspend_mode_is_broken = NULL;

	/* Reset if the controller isn't already safely quiescent. */
	check_and_reset_hc(uhci);
	return 0;
}

static const struct hc_driver uhci_grlib_hc_driver = {
	.description =		hcd_name,
	.product_desc =		"GRLIB GRUSBHC UHCI Host Controller",
	.hcd_priv_size =	sizeof(struct uhci_hcd),

	/* Generic hardware linkage */
	.irq =			uhci_irq,
	.flags =		HCD_MEMORY | HCD_USB11,

	/* Basic lifecycle operations */
	.reset =		uhci_grlib_init,
	.start =		uhci_start,
#ifdef CONFIG_PM
	.pci_suspend =		NULL,
	.pci_resume =		NULL,
	.bus_suspend =		uhci_rh_suspend,
	.bus_resume =		uhci_rh_resume,
#endif
	.stop =			uhci_stop,

	.urb_enqueue =		uhci_urb_enqueue,
	.urb_dequeue =		uhci_urb_dequeue,

	.endpoint_disable =	uhci_hcd_endpoint_disable,
	.get_frame_number =	uhci_hcd_get_frame_number,

	.hub_status_data =	uhci_hub_status_data,
	.hub_control =		uhci_hub_control,
};


static int uhci_hcd_grlib_probe(struct platform_device *op)
{
	struct device_node *dn = op->dev.of_node;
	struct usb_hcd *hcd;
	struct uhci_hcd	*uhci = NULL;
	struct resource res;
	int irq;
	int rv;

	if (usb_disabled())
		return -ENODEV;

	dev_dbg(&op->dev, "initializing GRUSBHC UHCI USB Controller\n");

	rv = of_address_to_resource(dn, 0, &res);
	if (rv)
		return rv;

	/* usb_create_hcd requires dma_mask != NULL */
	op->dev.dma_mask = &op->dev.coherent_dma_mask;
	hcd = usb_create_hcd(&uhci_grlib_hc_driver, &op->dev,
			"GRUSBHC UHCI USB");
	if (!hcd)
		return -ENOMEM;

	hcd->rsrc_start = res.start;
	hcd->rsrc_len = resource_size(&res);

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		printk(KERN_ERR "%s: request_mem_region failed\n", __FILE__);
		rv = -EBUSY;
		goto err_rmr;
	}

	irq = irq_of_parse_and_map(dn, 0);
	if (irq == NO_IRQ) {
		printk(KERN_ERR "%s: irq_of_parse_and_map failed\n", __FILE__);
		rv = -EBUSY;
		goto err_irq;
	}

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	if (!hcd->regs) {
		printk(KERN_ERR "%s: ioremap failed\n", __FILE__);
		rv = -ENOMEM;
		goto err_ioremap;
	}

	uhci = hcd_to_uhci(hcd);

	uhci->regs = hcd->regs;

	rv = usb_add_hcd(hcd, irq, 0);
	if (rv)
		goto err_uhci;

	return 0;

err_uhci:
	iounmap(hcd->regs);
err_ioremap:
	irq_dispose_mapping(irq);
err_irq:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
err_rmr:
	usb_put_hcd(hcd);

	return rv;
}

static int uhci_hcd_grlib_remove(struct platform_device *op)
{
	struct usb_hcd *hcd = dev_get_drvdata(&op->dev);

	dev_set_drvdata(&op->dev, NULL);

	dev_dbg(&op->dev, "stopping GRLIB GRUSBHC UHCI USB Controller\n");

	usb_remove_hcd(hcd);

	iounmap(hcd->regs);
	irq_dispose_mapping(hcd->irq);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);

	usb_put_hcd(hcd);

	return 0;
}

/* Make sure the controller is quiescent and that we're not using it
 * any more.  This is mainly for the benefit of programs which, like kexec,
 * expect the hardware to be idle: not doing DMA or generating IRQs.
 *
 * This routine may be called in a damaged or failing kernel.  Hence we
 * do not acquire the spinlock before shutting down the controller.
 */
static void uhci_hcd_grlib_shutdown(struct platform_device *op)
{
	struct usb_hcd *hcd = dev_get_drvdata(&op->dev);

	uhci_hc_died(hcd_to_uhci(hcd));
}

static const struct of_device_id uhci_hcd_grlib_of_match[] = {
	{ .name = "GAISLER_UHCI", },
	{ .name = "01_027", },
	{},
};
MODULE_DEVICE_TABLE(of, uhci_hcd_grlib_of_match);


static struct platform_driver uhci_grlib_driver = {
	.probe		= uhci_hcd_grlib_probe,
	.remove		= uhci_hcd_grlib_remove,
	.shutdown	= uhci_hcd_grlib_shutdown,
	.driver = {
		.name = "grlib-uhci",
		.owner = THIS_MODULE,
		.of_match_table = uhci_hcd_grlib_of_match,
	},
};
