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
#include <beep/gfp.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/tty.h>
#include <beep/tty_flip.h>
#include <beep/module.h>
#include <beep/usb.h>
#include <beep/usb/serial.h>

static const struct usb_device_id id_table[] = {
	{ USB_DEVICE(0x0a99, 0x0001) },	/* Talon Technology device */
	{ USB_DEVICE(0x0df7, 0x0900) },	/* Mobile Action i-gotU */
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static void navman_read_int_callback(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	unsigned char *data = urb->transfer_buffer;
	struct tty_struct *tty;
	int status = urb->status;
	int result;

	switch (status) {
	case 0:
		/* success */
		break;
	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&port->dev, "%s - urb shutting down with status: %d\n",
			__func__, status);
		return;
	default:
		dev_dbg(&port->dev, "%s - nonzero urb status received: %d\n",
			__func__, status);
		goto exit;
	}

	usb_serial_debug_data(&port->dev, __func__, urb->actual_length, data);

	tty = tty_port_tty_get(&port->port);
	if (tty && urb->actual_length) {
		tty_insert_flip_string(tty, data, urb->actual_length);
		tty_flip_buffer_push(tty);
	}
	tty_kref_put(tty);

exit:
	result = usb_submit_urb(urb, GFP_ATOMIC);
	if (result)
		dev_err(&urb->dev->dev,
			"%s - Error %d submitting interrupt urb\n",
			__func__, result);
}

static int navman_open(struct tty_struct *tty, struct usb_serial_port *port)
{
	int result = 0;

	if (port->interrupt_in_urb) {
		dev_dbg(&port->dev, "%s - adding interrupt input for treo\n",
			__func__);
		result = usb_submit_urb(port->interrupt_in_urb, GFP_KERNEL);
		if (result)
			dev_err(&port->dev,
				"%s - failed submitting interrupt urb, error %d\n",
				__func__, result);
	}
	return result;
}

static void navman_close(struct usb_serial_port *port)
{
	usb_kill_urb(port->interrupt_in_urb);
}

static int navman_write(struct tty_struct *tty, struct usb_serial_port *port,
			const unsigned char *buf, int count)
{
	/*
	 * This device can't write any data, only read from the device
	 */
	return -EOPNOTSUPP;
}

static struct usb_serial_driver navman_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"navman",
	},
	.id_table =		id_table,
	.num_ports =		1,
	.open =			navman_open,
	.close = 		navman_close,
	.write = 		navman_write,
	.read_int_callback =	navman_read_int_callback,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&navman_device, NULL
};

module_usb_serial_driver(serial_drivers, id_table);

MODULE_LICENSE("GPL");
