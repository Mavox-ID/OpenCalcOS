/*
 * Funsoft Serial USB driver
 *
 * Copyright (C) 2006 Greg Kroah-Hartman <gregkh@suse.de>
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
	{ USB_DEVICE(0x1404, 0xcddc) },
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_serial_driver funsoft_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"funsoft",
	},
	.id_table =		id_table,
	.num_ports =		1,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&funsoft_device, NULL
};

module_usb_serial_driver(serial_drivers, id_table);

MODULE_LICENSE("GPL");
