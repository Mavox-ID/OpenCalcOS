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
#ifndef VARIAX_H
#define VARIAX_H

#include <beep/spinlock.h>
#include <beep/usb.h>
#include <beep/wait.h>
#include <sound/core.h>

#include "driver.h"

#define VARIAX_STARTUP_DELAY1 1000
#define VARIAX_STARTUP_DELAY3 100
#define VARIAX_STARTUP_DELAY4 100

/*
	Stages of Variax startup procedure
*/
enum {
	VARIAX_STARTUP_INIT = 1,
	VARIAX_STARTUP_VERSIONREQ,
	VARIAX_STARTUP_WAIT,
	VARIAX_STARTUP_ACTIVATE,
	VARIAX_STARTUP_WORKQUEUE,
	VARIAX_STARTUP_SETUP,
	VARIAX_STARTUP_LAST = VARIAX_STARTUP_SETUP - 1
};

struct usb_line6_variax {
	/**
		Generic Line6 USB data.
	*/
	struct usb_line6 line6;

	/**
		Buffer for activation code.
	*/
	unsigned char *buffer_activate;

	/**
		Handler for device initializaton.
	*/
	struct work_struct startup_work;

	/**
		Timers for device initializaton.
	*/
	struct timer_list startup_timer1;
	struct timer_list startup_timer2;

	/**
		Current progress in startup procedure.
	*/
	int startup_progress;
};

extern void line6_variax_disconnect(struct usb_interface *interface);
extern int line6_variax_init(struct usb_interface *interface,
			     struct usb_line6_variax *variax);
extern void line6_variax_process_message(struct usb_line6_variax *variax);

#endif
