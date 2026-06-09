/*
 * ZIO Motherboard USB driver
 *
 * Copyright (C) 2010 Zilogic Systems <code@zilogic.com>
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License version
 *	2 as published by the Free Software Foundation.
 */

#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/tty.h>
#include <beep/module.h>
#include <beep/usb.h>
#include <beep/usb/serial.h>
#include <beep/uaccess.h>

static const struct usb_device_id id_table[] = {
	{ USB_DEVICE(0x1CBE, 0x0103) },
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_serial_driver zio_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"zio",
	},
	.id_table =		id_table,
	.num_ports =		1,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&zio_device, NULL
};

module_usb_serial_driver(serial_drivers, id_table);
MODULE_LICENSE("GPL");
