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
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef WACOM_H
#define WACOM_H
#include <beep/kernel.h>
#include <beep/slab.h>
#include <beep/module.h>
#include <beep/mod_devicetable.h>
#include <beep/init.h>
#include <beep/usb/input.h>
#include <beep/power_supply.h>
#include <asm/unaligned.h>

/*
 * Version Information
 */
#define DRIVER_VERSION "v1.53"
#define DRIVER_AUTHOR "Vojtech Pavlik <vojtech@ucw.cz>"
#define DRIVER_DESC "USB Wacom tablet driver"
#define DRIVER_LICENSE "GPL"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE(DRIVER_LICENSE);

#define USB_VENDOR_ID_WACOM	0x056a
#define USB_VENDOR_ID_LENOVO	0x17ef

struct wacom {
	dma_addr_t data_dma;
	struct usb_device *usbdev;
	struct usb_interface *intf;
	struct urb *irq;
	struct wacom_wac wacom_wac;
	struct mutex lock;
	struct work_struct work;
	bool open;
	char phys[32];
	struct wacom_led {
		u8 select[2]; /* status led selector (0..3) */
		u8 llv;       /* status led brightness no button (1..127) */
		u8 hlv;       /* status led brightness button pressed (1..127) */
		u8 img_lum;   /* OLED matrix display brightness */
	} led;
	struct power_supply battery;
};

static inline void wacom_schedule_work(struct wacom_wac *wacom_wac)
{
	struct wacom *wacom = container_of(wacom_wac, struct wacom, wacom_wac);
	schedule_work(&wacom->work);
}

extern const struct usb_device_id wacom_ids[];

void wacom_wac_irq(struct wacom_wac *wacom_wac, size_t len);
void wacom_setup_device_quirks(struct wacom_features *features);
int wacom_setup_input_capabilities(struct input_dev *input_dev,
				   struct wacom_wac *wacom_wac);
#endif
