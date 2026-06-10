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
#include <beep/export.h>
#include <beep/notifier.h>
#include <beep/usb.h>
#include <beep/mutex.h>
#include "usb.h"

static BLOCKING_NOTIFIER_HEAD(usb_notifier_list);

/**
 * usb_register_notify - register a notifier callback whenever a usb change happens
 * @nb: pointer to the notifier block for the callback events.
 *
 * These changes are either USB devices or busses being added or removed.
 */
void usb_register_notify(struct notifier_block *nb)
{
	blocking_notifier_chain_register(&usb_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(usb_register_notify);

/**
 * usb_unregister_notify - unregister a notifier callback
 * @nb: pointer to the notifier block for the callback events.
 *
 * usb_register_notify() must have been previously called for this function
 * to work properly.
 */
void usb_unregister_notify(struct notifier_block *nb)
{
	blocking_notifier_chain_unregister(&usb_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(usb_unregister_notify);


void usb_notify_add_device(struct usb_device *udev)
{
	blocking_notifier_call_chain(&usb_notifier_list, USB_DEVICE_ADD, udev);
}

void usb_notify_remove_device(struct usb_device *udev)
{
	/* Protect against simultaneous usbfs open */
	mutex_lock(&usbfs_mutex);
	blocking_notifier_call_chain(&usb_notifier_list,
			USB_DEVICE_REMOVE, udev);
	mutex_unlock(&usbfs_mutex);
}

void usb_notify_add_bus(struct usb_bus *ubus)
{
	blocking_notifier_call_chain(&usb_notifier_list, USB_BUS_ADD, ubus);
}

void usb_notify_remove_bus(struct usb_bus *ubus)
{
	blocking_notifier_call_chain(&usb_notifier_list, USB_BUS_REMOVE, ubus);
}
