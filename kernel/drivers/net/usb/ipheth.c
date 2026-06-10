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
#include <beep/errno.h>
#include <beep/init.h>
#include <beep/slab.h>
#include <beep/module.h>
#include <beep/netdevice.h>
#include <beep/etherdevice.h>
#include <beep/ethtool.h>
#include <beep/usb.h>
#include <beep/workqueue.h>

#define USB_VENDOR_APPLE        0x05ac
#define USB_PRODUCT_IPHONE      0x1290
#define USB_PRODUCT_IPHONE_3G   0x1292
#define USB_PRODUCT_IPHONE_3GS  0x1294
#define USB_PRODUCT_IPHONE_4	0x1297
#define USB_PRODUCT_IPAD 0x129a
#define USB_PRODUCT_IPHONE_4_VZW 0x129c
#define USB_PRODUCT_IPHONE_4S	0x12a0
#define USB_PRODUCT_IPHONE_5	0x12a8

#define IPHETH_USBINTF_CLASS    255
#define IPHETH_USBINTF_SUBCLASS 253
#define IPHETH_USBINTF_PROTO    1

#define IPHETH_BUF_SIZE         1516
#define IPHETH_IP_ALIGN		2	/* padding at front of URB */
#define IPHETH_TX_TIMEOUT       (5 * HZ)

#define IPHETH_INTFNUM          2
#define IPHETH_ALT_INTFNUM      1

#define IPHETH_CTRL_ENDP        0x00
#define IPHETH_CTRL_BUF_SIZE    0x40
#define IPHETH_CTRL_TIMEOUT     (5 * HZ)

#define IPHETH_CMD_GET_MACADDR   0x00
#define IPHETH_CMD_CARRIER_CHECK 0x45

#define IPHETH_CARRIER_CHECK_TIMEOUT round_jiffies_relative(1 * HZ)
#define IPHETH_CARRIER_ON       0x04

static struct usb_device_id ipheth_table[] = {
	{ USB_DEVICE_AND_INTERFACE_INFO(
		USB_VENDOR_APPLE, USB_PRODUCT_IPHONE,
		IPHETH_USBINTF_CLASS, IPHETH_USBINTF_SUBCLASS,
		IPHETH_USBINTF_PROTO) },
	{ USB_DEVICE_AND_INTERFACE_INFO(
		USB_VENDOR_APPLE, USB_PRODUCT_IPHONE_3G,
		IPHETH_USBINTF_CLASS, IPHETH_USBINTF_SUBCLASS,
		IPHETH_USBINTF_PROTO) },
	{ USB_DEVICE_AND_INTERFACE_INFO(
		USB_VENDOR_APPLE, USB_PRODUCT_IPHONE_3GS,
		IPHETH_USBINTF_CLASS, IPHETH_USBINTF_SUBCLASS,
		IPHETH_USBINTF_PROTO) },
	{ USB_DEVICE_AND_INTERFACE_INFO(
		USB_VENDOR_APPLE, USB_PRODUCT_IPHONE_4,
		IPHETH_USBINTF_CLASS, IPHETH_USBINTF_SUBCLASS,
		IPHETH_USBINTF_PROTO) },
	{ USB_DEVICE_AND_INTERFACE_INFO(
		USB_VENDOR_APPLE, USB_PRODUCT_IPAD,
		IPHETH_USBINTF_CLASS, IPHETH_USBINTF_SUBCLASS,
		IPHETH_USBINTF_PROTO) },
	{ USB_DEVICE_AND_INTERFACE_INFO(
		USB_VENDOR_APPLE, USB_PRODUCT_IPHONE_4_VZW,
		IPHETH_USBINTF_CLASS, IPHETH_USBINTF_SUBCLASS,
		IPHETH_USBINTF_PROTO) },
	{ USB_DEVICE_AND_INTERFACE_INFO(
		USB_VENDOR_APPLE, USB_PRODUCT_IPHONE_4S,
		IPHETH_USBINTF_CLASS, IPHETH_USBINTF_SUBCLASS,
		IPHETH_USBINTF_PROTO) },
	{ USB_DEVICE_AND_INTERFACE_INFO(
		USB_VENDOR_APPLE, USB_PRODUCT_IPHONE_5,
		IPHETH_USBINTF_CLASS, IPHETH_USBINTF_SUBCLASS,
		IPHETH_USBINTF_PROTO) },
	{ }
};
MODULE_DEVICE_TABLE(usb, ipheth_table);

struct ipheth_device {
	struct usb_device *udev;
	struct usb_interface *intf;
	struct net_device *net;
	struct sk_buff *tx_skb;
	struct urb *tx_urb;
	struct urb *rx_urb;
	unsigned char *tx_buf;
	unsigned char *rx_buf;
	unsigned char *ctrl_buf;
	u8 bulk_in;
	u8 bulk_out;
	struct delayed_work carrier_work;
};

static int ipheth_rx_submit(struct ipheth_device *dev, gfp_t mem_flags);

static int ipheth_alloc_urbs(struct ipheth_device *iphone)
{
	struct urb *tx_urb = NULL;
	struct urb *rx_urb = NULL;
	u8 *tx_buf = NULL;
	u8 *rx_buf = NULL;

	tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (tx_urb == NULL)
		goto error_nomem;

	rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (rx_urb == NULL)
		goto free_tx_urb;

	tx_buf = usb_alloc_coherent(iphone->udev, IPHETH_BUF_SIZE,
				    GFP_KERNEL, &tx_urb->transfer_dma);
	if (tx_buf == NULL)
		goto free_rx_urb;

	rx_buf = usb_alloc_coherent(iphone->udev, IPHETH_BUF_SIZE,
				    GFP_KERNEL, &rx_urb->transfer_dma);
	if (rx_buf == NULL)
		goto free_tx_buf;


	iphone->tx_urb = tx_urb;
	iphone->rx_urb = rx_urb;
	iphone->tx_buf = tx_buf;
	iphone->rx_buf = rx_buf;
	return 0;

free_tx_buf:
	usb_free_coherent(iphone->udev, IPHETH_BUF_SIZE, tx_buf,
			  tx_urb->transfer_dma);
free_rx_urb:
	usb_free_urb(rx_urb);
free_tx_urb:
	usb_free_urb(tx_urb);
error_nomem:
	return -ENOMEM;
}

static void ipheth_free_urbs(struct ipheth_device *iphone)
{
	usb_free_coherent(iphone->udev, IPHETH_BUF_SIZE, iphone->rx_buf,
			  iphone->rx_urb->transfer_dma);
	usb_free_coherent(iphone->udev, IPHETH_BUF_SIZE, iphone->tx_buf,
			  iphone->tx_urb->transfer_dma);
	usb_free_urb(iphone->rx_urb);
	usb_free_urb(iphone->tx_urb);
}

static void ipheth_kill_urbs(struct ipheth_device *dev)
{
	usb_kill_urb(dev->tx_urb);
	usb_kill_urb(dev->rx_urb);
}

static void ipheth_rcvbulk_callback(struct urb *urb)
{
	struct ipheth_device *dev;
	struct sk_buff *skb;
	int status;
	char *buf;
	int len;

	dev = urb->context;
	if (dev == NULL)
		return;

	status = urb->status;
	switch (status) {
	case -ENOENT:
	case -ECONNRESET:
	case -ESHUTDOWN:
		return;
	case 0:
		break;
	default:
		dev_err(&dev->intf->dev, "%s: urb status: %d\n",
			__func__, status);
		return;
	}

	if (urb->actual_length <= IPHETH_IP_ALIGN) {
		dev->net->stats.rx_length_errors++;
		return;
	}
	len = urb->actual_length - IPHETH_IP_ALIGN;
	buf = urb->transfer_buffer + IPHETH_IP_ALIGN;

	skb = dev_alloc_skb(len);
	if (!skb) {
		dev_err(&dev->intf->dev, "%s: dev_alloc_skb: -ENOMEM\n",
			__func__);
		dev->net->stats.rx_dropped++;
		return;
	}

	memcpy(skb_put(skb, len), buf, len);
	skb->dev = dev->net;
	skb->protocol = eth_type_trans(skb, dev->net);

	dev->net->stats.rx_packets++;
	dev->net->stats.rx_bytes += len;

	netif_rx(skb);
	ipheth_rx_submit(dev, GFP_ATOMIC);
}

static void ipheth_sndbulk_callback(struct urb *urb)
{
	struct ipheth_device *dev;
	int status = urb->status;

	dev = urb->context;
	if (dev == NULL)
		return;

	if (status != 0 &&
	    status != -ENOENT &&
	    status != -ECONNRESET &&
	    status != -ESHUTDOWN)
		dev_err(&dev->intf->dev, "%s: urb status: %d\n",
		__func__, status);

	dev_kfree_skb_irq(dev->tx_skb);
	netif_wake_queue(dev->net);
}

static int ipheth_carrier_set(struct ipheth_device *dev)
{
	struct usb_device *udev = dev->udev;
	int retval;

	retval = usb_control_msg(udev,
			usb_rcvctrlpipe(udev, IPHETH_CTRL_ENDP),
			IPHETH_CMD_CARRIER_CHECK, /* request */
			0xc0, /* request type */
			0x00, /* value */
			0x02, /* index */
			dev->ctrl_buf, IPHETH_CTRL_BUF_SIZE,
			IPHETH_CTRL_TIMEOUT);
	if (retval < 0) {
		dev_err(&dev->intf->dev, "%s: usb_control_msg: %d\n",
			__func__, retval);
		return retval;
	}

	if (dev->ctrl_buf[0] == IPHETH_CARRIER_ON)
		netif_carrier_on(dev->net);
	else
		netif_carrier_off(dev->net);

	return 0;
}

static void ipheth_carrier_check_work(struct work_struct *work)
{
	struct ipheth_device *dev = container_of(work, struct ipheth_device,
						 carrier_work.work);

	ipheth_carrier_set(dev);
	schedule_delayed_work(&dev->carrier_work, IPHETH_CARRIER_CHECK_TIMEOUT);
}

static int ipheth_get_macaddr(struct ipheth_device *dev)
{
	struct usb_device *udev = dev->udev;
	struct net_device *net = dev->net;
	int retval;

	retval = usb_control_msg(udev,
				 usb_rcvctrlpipe(udev, IPHETH_CTRL_ENDP),
				 IPHETH_CMD_GET_MACADDR, /* request */
				 0xc0, /* request type */
				 0x00, /* value */
				 0x02, /* index */
				 dev->ctrl_buf,
				 IPHETH_CTRL_BUF_SIZE,
				 IPHETH_CTRL_TIMEOUT);
	if (retval < 0) {
		dev_err(&dev->intf->dev, "%s: usb_control_msg: %d\n",
			__func__, retval);
	} else if (retval < ETH_ALEN) {
		dev_err(&dev->intf->dev,
			"%s: usb_control_msg: short packet: %d bytes\n",
			__func__, retval);
		retval = -EINVAL;
	} else {
		memcpy(net->dev_addr, dev->ctrl_buf, ETH_ALEN);
		retval = 0;
	}

	return retval;
}

static int ipheth_rx_submit(struct ipheth_device *dev, gfp_t mem_flags)
{
	struct usb_device *udev = dev->udev;
	int retval;

	usb_fill_bulk_urb(dev->rx_urb, udev,
			  usb_rcvbulkpipe(udev, dev->bulk_in),
			  dev->rx_buf, IPHETH_BUF_SIZE,
			  ipheth_rcvbulk_callback,
			  dev);
	dev->rx_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	retval = usb_submit_urb(dev->rx_urb, mem_flags);
	if (retval)
		dev_err(&dev->intf->dev, "%s: usb_submit_urb: %d\n",
			__func__, retval);
	return retval;
}

static int ipheth_open(struct net_device *net)
{
	struct ipheth_device *dev = netdev_priv(net);
	struct usb_device *udev = dev->udev;
	int retval = 0;

	usb_set_interface(udev, IPHETH_INTFNUM, IPHETH_ALT_INTFNUM);

	retval = ipheth_carrier_set(dev);
	if (retval)
		return retval;

	retval = ipheth_rx_submit(dev, GFP_KERNEL);
	if (retval)
		return retval;

	schedule_delayed_work(&dev->carrier_work, IPHETH_CARRIER_CHECK_TIMEOUT);
	netif_start_queue(net);
	return retval;
}

static int ipheth_close(struct net_device *net)
{
	struct ipheth_device *dev = netdev_priv(net);

	cancel_delayed_work_sync(&dev->carrier_work);
	netif_stop_queue(net);
	return 0;
}

static int ipheth_tx(struct sk_buff *skb, struct net_device *net)
{
	struct ipheth_device *dev = netdev_priv(net);
	struct usb_device *udev = dev->udev;
	int retval;

	/* Paranoid */
	if (skb->len > IPHETH_BUF_SIZE) {
		WARN(1, "%s: skb too large: %d bytes\n", __func__, skb->len);
		dev->net->stats.tx_dropped++;
		dev_kfree_skb_irq(skb);
		return NETDEV_TX_OK;
	}

	memcpy(dev->tx_buf, skb->data, skb->len);
	if (skb->len < IPHETH_BUF_SIZE)
		memset(dev->tx_buf + skb->len, 0, IPHETH_BUF_SIZE - skb->len);

	usb_fill_bulk_urb(dev->tx_urb, udev,
			  usb_sndbulkpipe(udev, dev->bulk_out),
			  dev->tx_buf, IPHETH_BUF_SIZE,
			  ipheth_sndbulk_callback,
			  dev);
	dev->tx_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	retval = usb_submit_urb(dev->tx_urb, GFP_ATOMIC);
	if (retval) {
		dev_err(&dev->intf->dev, "%s: usb_submit_urb: %d\n",
			__func__, retval);
		dev->net->stats.tx_errors++;
		dev_kfree_skb_irq(skb);
	} else {
		dev->tx_skb = skb;

		dev->net->stats.tx_packets++;
		dev->net->stats.tx_bytes += skb->len;
		netif_stop_queue(net);
	}

	return NETDEV_TX_OK;
}

static void ipheth_tx_timeout(struct net_device *net)
{
	struct ipheth_device *dev = netdev_priv(net);

	dev_err(&dev->intf->dev, "%s: TX timeout\n", __func__);
	dev->net->stats.tx_errors++;
	usb_unlink_urb(dev->tx_urb);
}

static u32 ipheth_ethtool_op_get_link(struct net_device *net)
{
	struct ipheth_device *dev = netdev_priv(net);
	return netif_carrier_ok(dev->net);
}

static const struct ethtool_ops ops = {
	.get_link = ipheth_ethtool_op_get_link
};

static const struct net_device_ops ipheth_netdev_ops = {
	.ndo_open = ipheth_open,
	.ndo_stop = ipheth_close,
	.ndo_start_xmit = ipheth_tx,
	.ndo_tx_timeout = ipheth_tx_timeout,
};

static int ipheth_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct usb_host_interface *hintf;
	struct usb_endpoint_descriptor *endp;
	struct ipheth_device *dev;
	struct net_device *netdev;
	int i;
	int retval;

	netdev = alloc_etherdev(sizeof(struct ipheth_device));
	if (!netdev)
		return -ENOMEM;

	netdev->netdev_ops = &ipheth_netdev_ops;
	netdev->watchdog_timeo = IPHETH_TX_TIMEOUT;
	strcpy(netdev->name, "eth%d");

	dev = netdev_priv(netdev);
	dev->udev = udev;
	dev->net = netdev;
	dev->intf = intf;

	/* Set up endpoints */
	hintf = usb_altnum_to_altsetting(intf, IPHETH_ALT_INTFNUM);
	if (hintf == NULL) {
		retval = -ENODEV;
		dev_err(&intf->dev, "Unable to find alternate settings interface\n");
		goto err_endpoints;
	}

	for (i = 0; i < hintf->desc.bNumEndpoints; i++) {
		endp = &hintf->endpoint[i].desc;
		if (usb_endpoint_is_bulk_in(endp))
			dev->bulk_in = endp->bEndpointAddress;
		else if (usb_endpoint_is_bulk_out(endp))
			dev->bulk_out = endp->bEndpointAddress;
	}
	if (!(dev->bulk_in && dev->bulk_out)) {
		retval = -ENODEV;
		dev_err(&intf->dev, "Unable to find endpoints\n");
		goto err_endpoints;
	}

	dev->ctrl_buf = kmalloc(IPHETH_CTRL_BUF_SIZE, GFP_KERNEL);
	if (dev->ctrl_buf == NULL) {
		retval = -ENOMEM;
		goto err_alloc_ctrl_buf;
	}

	retval = ipheth_get_macaddr(dev);
	if (retval)
		goto err_get_macaddr;

	INIT_DELAYED_WORK(&dev->carrier_work, ipheth_carrier_check_work);

	retval = ipheth_alloc_urbs(dev);
	if (retval) {
		dev_err(&intf->dev, "error allocating urbs: %d\n", retval);
		goto err_alloc_urbs;
	}

	usb_set_intfdata(intf, dev);

	SET_NETDEV_DEV(netdev, &intf->dev);
	SET_ETHTOOL_OPS(netdev, &ops);

	retval = register_netdev(netdev);
	if (retval) {
		dev_err(&intf->dev, "error registering netdev: %d\n", retval);
		retval = -EIO;
		goto err_register_netdev;
	}

	dev_info(&intf->dev, "Apple iPhone USB Ethernet device attached\n");
	return 0;

err_register_netdev:
	ipheth_free_urbs(dev);
err_alloc_urbs:
err_get_macaddr:
err_alloc_ctrl_buf:
	kfree(dev->ctrl_buf);
err_endpoints:
	free_netdev(netdev);
	return retval;
}

static void ipheth_disconnect(struct usb_interface *intf)
{
	struct ipheth_device *dev;

	dev = usb_get_intfdata(intf);
	if (dev != NULL) {
		unregister_netdev(dev->net);
		ipheth_kill_urbs(dev);
		ipheth_free_urbs(dev);
		kfree(dev->ctrl_buf);
		free_netdev(dev->net);
	}
	usb_set_intfdata(intf, NULL);
	dev_info(&intf->dev, "Apple iPhone USB Ethernet now disconnected\n");
}

static struct usb_driver ipheth_driver = {
	.name =		"ipheth",
	.probe =	ipheth_probe,
	.disconnect =	ipheth_disconnect,
	.id_table =	ipheth_table,
	.disable_hub_initiated_lpm = 1,
};

module_usb_driver(ipheth_driver);

MODULE_AUTHOR("Diego Giagio <diego@giagio.com>");
MODULE_DESCRIPTION("Apple iPhone USB Ethernet driver");
MODULE_LICENSE("Dual BSD/GPL");
