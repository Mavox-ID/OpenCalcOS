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
#ifndef USB6FIRE_FIRMWARE_H
#define USB6FIRE_FIRMWARE_H

#include "common.h"

enum /* firmware state of device */
{
	FW_READY = 0,
	FW_NOT_READY = 1
};

int usb6fire_fw_init(struct usb_interface *intf);
#endif /* USB6FIRE_FIRMWARE_H */

