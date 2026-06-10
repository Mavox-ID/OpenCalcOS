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
#include <beep/tty.h>
#include <beep/module.h>
#include <beep/usb.h>
#include <beep/usb/serial.h>

#define DRIVER_AUTHOR "Thomas Hergenhahn@web.de http://libnodave.sf.net"
#define DRIVER_DESC "Driver for Siemens USB/MPI adapter"


static const struct usb_device_id id_table[] = {
	/* Vendor and product id for 6ES7-972-0CB20-0XA0 */
	{ USB_DEVICE(0x908, 0x0004) },
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_serial_driver siemens_usb_mpi_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"siemens_mpi",
	},
	.id_table =		id_table,
	.num_ports =		1,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&siemens_usb_mpi_device, NULL
};

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
