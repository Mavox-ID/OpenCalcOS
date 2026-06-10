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
#include <asm/unaligned.h>
#include <beep/tty.h>
#include <beep/slab.h>
#include <beep/module.h>
#include <beep/tty_flip.h>
#include <beep/usb.h>
#include <beep/usb/serial.h>

/* Vendor and Product ID */
#define AIRCABLE_VID		0x16CA
#define AIRCABLE_USB_PID	0x1502

/* Protocol Stuff */
#define HCI_HEADER_LENGTH	0x4
#define TX_HEADER_0		0x20
#define TX_HEADER_1		0x29
#define RX_HEADER_0		0x00
#define RX_HEADER_1		0x20
#define HCI_COMPLETE_FRAME	64

/* rx_flags */
#define THROTTLED		0x01
#define ACTUALLY_THROTTLED	0x02

#define DRIVER_AUTHOR "Naranjo, Manuel Francisco <naranjo.manuel@gmail.com>, Johan Hovold <jhovold@gmail.com>"
#define DRIVER_DESC "AIRcable USB Driver"

/* ID table that will be registered with USB core */
static const struct usb_device_id id_table[] = {
	{ USB_DEVICE(AIRCABLE_VID, AIRCABLE_USB_PID) },
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static int aircable_prepare_write_buffer(struct usb_serial_port *port,
						void *dest, size_t size)
{
	int count;
	unsigned char *buf = dest;

	count = kfifo_out_locked(&port->write_fifo, buf + HCI_HEADER_LENGTH,
					size - HCI_HEADER_LENGTH, &port->lock);
	buf[0] = TX_HEADER_0;
	buf[1] = TX_HEADER_1;
	put_unaligned_le16(count, &buf[2]);

	return count + HCI_HEADER_LENGTH;
}

static int aircable_probe(struct usb_serial *serial,
			  const struct usb_device_id *id)
{
	struct usb_host_interface *iface_desc = serial->interface->
								cur_altsetting;
	struct usb_endpoint_descriptor *endpoint;
	int num_bulk_out = 0;
	int i;

	for (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
		endpoint = &iface_desc->endpoint[i].desc;
		if (usb_endpoint_is_bulk_out(endpoint)) {
			dev_dbg(&serial->dev->dev,
				"found bulk out on endpoint %d\n", i);
			++num_bulk_out;
		}
	}

	if (num_bulk_out == 0) {
		dev_dbg(&serial->dev->dev, "Invalid interface, discarding\n");
		return -ENODEV;
	}

	return 0;
}

static int aircable_process_packet(struct tty_struct *tty,
			struct usb_serial_port *port, int has_headers,
			char *packet, int len)
{
	if (has_headers) {
		len -= HCI_HEADER_LENGTH;
		packet += HCI_HEADER_LENGTH;
	}
	if (len <= 0) {
		dev_dbg(&port->dev, "%s - malformed packet\n", __func__);
		return 0;
	}

	tty_insert_flip_string(tty, packet, len);

	return len;
}

static void aircable_process_read_urb(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	char *data = (char *)urb->transfer_buffer;
	struct tty_struct *tty;
	int has_headers;
	int count;
	int len;
	int i;

	tty = tty_port_tty_get(&port->port);
	if (!tty)
		return;

	has_headers = (urb->actual_length > 2 && data[0] == RX_HEADER_0);

	count = 0;
	for (i = 0; i < urb->actual_length; i += HCI_COMPLETE_FRAME) {
		len = min_t(int, urb->actual_length - i, HCI_COMPLETE_FRAME);
		count += aircable_process_packet(tty, port, has_headers,
								&data[i], len);
	}

	if (count)
		tty_flip_buffer_push(tty);
	tty_kref_put(tty);
}

static struct usb_serial_driver aircable_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"aircable",
	},
	.id_table = 		id_table,
	.num_ports =		1,
	.bulk_out_size =	HCI_COMPLETE_FRAME,
	.probe =		aircable_probe,
	.process_read_urb =	aircable_process_read_urb,
	.prepare_write_buffer =	aircable_prepare_write_buffer,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&aircable_device, NULL
};

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
