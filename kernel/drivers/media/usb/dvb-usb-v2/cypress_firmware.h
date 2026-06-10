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
#ifndef CYPRESS_FIRMWARE_H
#define CYPRESS_FIRMWARE_H

#define CYPRESS_AN2135  0
#define CYPRESS_AN2235  1
#define CYPRESS_FX2     2

/* commonly used firmware download types and function */
struct hexline {
	u8 len;
	u32 addr;
	u8 type;
	u8 data[255];
	u8 chk;
};
extern int usbv2_cypress_load_firmware(struct usb_device *,
		const struct firmware *, int);
extern int dvb_usbv2_get_hexline(const struct firmware *,
		struct hexline *, int *);

#endif
