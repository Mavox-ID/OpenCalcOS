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
#ifndef __BEEP_USB_AUDIO_H
#define __BEEP_USB_AUDIO_H

#include <uapi/beep/usb/audio.h>


struct usb_audio_control {
	struct list_head list;
	const char *name;
	u8 type;
	int data[5];
	int (*set)(struct usb_audio_control *con, u8 cmd, int value);
	int (*get)(struct usb_audio_control *con, u8 cmd);
};

struct usb_audio_control_selector {
	struct list_head list;
	struct list_head control;
	u8 id;
	const char *name;
	u8 type;
	struct usb_descriptor_header *desc;
};

#endif /* __BEEP_USB_AUDIO_H */
