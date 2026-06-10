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

/* NOTE: for now, only use this driver for devices that provide a CDC-ACM port
 * for normal AT commands, but also provide secondary USB interfaces for the
 * QCDM-capable ports.  Devices that do not provide a CDC-ACM port should
 * probably be driven by option.ko.
 */

/* UTStarcom/Pantech/Curitel devices */
#define UTSTARCOM_VENDOR_ID			0x106c
#define UTSTARCOM_PRODUCT_PC5740		0x3701
#define UTSTARCOM_PRODUCT_PC5750		0x3702 /* aka Pantech PX-500 */
#define UTSTARCOM_PRODUCT_UM150			0x3711
#define UTSTARCOM_PRODUCT_UM175_V1		0x3712
#define UTSTARCOM_PRODUCT_UM175_V2		0x3714
#define UTSTARCOM_PRODUCT_UM175_ALLTEL		0x3715

/* CMOTECH devices */
#define CMOTECH_VENDOR_ID			0x16d8
#define CMOTECH_PRODUCT_CDU550			0x5553
#define CMOTECH_PRODUCT_CDX650			0x6512

/* LG devices */
#define LG_VENDOR_ID				0x1004
#define LG_PRODUCT_VX4400_6000			0x6000 /* VX4400/VX6000/Rumor */

/* Sanyo devices */
#define SANYO_VENDOR_ID				0x0474
#define SANYO_PRODUCT_KATANA_LX			0x0754 /* SCP-3800 (Katana LX) */

/* Samsung devices */
#define SAMSUNG_VENDOR_ID			0x04e8
#define SAMSUNG_PRODUCT_U520			0x6640 /* SCH-U520 */

static struct usb_device_id id_table[] = {
	{ USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_PC5740, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_PC5750, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_UM150, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_UM175_V1, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_UM175_V2, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, UTSTARCOM_PRODUCT_UM175_ALLTEL, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTERFACE_INFO(CMOTECH_VENDOR_ID, CMOTECH_PRODUCT_CDU550, 0xff, 0xff, 0x00) },
	{ USB_DEVICE_AND_INTERFACE_INFO(CMOTECH_VENDOR_ID, CMOTECH_PRODUCT_CDX650, 0xff, 0xff, 0x00) },
	{ USB_DEVICE_AND_INTERFACE_INFO(LG_VENDOR_ID, LG_PRODUCT_VX4400_6000, 0xff, 0xff, 0x00) },
	{ USB_DEVICE_AND_INTERFACE_INFO(SANYO_VENDOR_ID, SANYO_PRODUCT_KATANA_LX, 0xff, 0xff, 0x00) },
	{ USB_DEVICE_AND_INTERFACE_INFO(SAMSUNG_VENDOR_ID, SAMSUNG_PRODUCT_U520, 0xff, 0x00, 0x00) },
	{ USB_VENDOR_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, 0xff, 0xfd, 0xff) },  /* NMEA */
	{ USB_VENDOR_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, 0xff, 0xfe, 0xff) },  /* WMC */
	{ USB_VENDOR_AND_INTERFACE_INFO(UTSTARCOM_VENDOR_ID, 0xff, 0xff, 0xff) },  /* DIAG */
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_serial_driver qcaux_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"qcaux",
	},
	.id_table =		id_table,
	.num_ports =		1,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&qcaux_device, NULL
};

module_usb_serial_driver(serial_drivers, id_table);
MODULE_LICENSE("GPL");
