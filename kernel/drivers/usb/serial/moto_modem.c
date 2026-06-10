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

static const struct usb_device_id id_table[] = {
	{ USB_DEVICE(0x05c6, 0x3197) },	/* unknown Motorola phone */
	{ USB_DEVICE(0x0c44, 0x0022) },	/* unknown Mororola phone */
	{ USB_DEVICE(0x22b8, 0x2a64) },	/* Motorola KRZR K1m */
	{ USB_DEVICE(0x22b8, 0x2c84) }, /* Motorola VE240 phone */
	{ USB_DEVICE(0x22b8, 0x2c64) }, /* Motorola V950 phone */
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_serial_driver moto_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"moto-modem",
	},
	.id_table =		id_table,
	.num_ports =		1,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&moto_device, NULL
};

module_usb_serial_driver(serial_drivers, id_table);
MODULE_LICENSE("GPL");
