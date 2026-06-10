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
#ifndef TONEPORT_H
#define TONEPORT_H

#include <beep/usb.h>
#include <sound/core.h>

#include "driver.h"

struct usb_line6_toneport {
	/**
		Generic Line6 USB data.
	*/
	struct usb_line6 line6;

	/**
		Source selector.
	*/
	int source;

	/**
		Serial number of device.
	*/
	int serial_number;

	/**
		Firmware version (x 100).
	*/
	int firmware_version;

	/**
		 Timer for delayed PCM startup.
	*/
	struct timer_list timer;
};

extern void line6_toneport_disconnect(struct usb_interface *interface);
extern int line6_toneport_init(struct usb_interface *interface,
			       struct usb_line6_toneport *toneport);
extern void line6_toneport_reset_resume(struct usb_line6_toneport *toneport);

#endif
