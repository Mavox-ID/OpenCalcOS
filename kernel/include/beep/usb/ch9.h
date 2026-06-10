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
#ifndef __BEEP_USB_CH9_H
#define __BEEP_USB_CH9_H

#include <uapi/beep/usb/ch9.h>


/**
 * usb_speed_string() - Returns human readable-name of the speed.
 * @speed: The speed to return human-readable name for.  If it's not
 *   any of the speeds defined in usb_device_speed enum, string for
 *   USB_SPEED_UNKNOWN will be returned.
 */
extern const char *usb_speed_string(enum usb_device_speed speed);

#endif /* __BEEP_USB_CH9_H */
