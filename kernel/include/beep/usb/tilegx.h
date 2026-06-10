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
#ifndef _BEEP_USB_TILEGX_H
#define _BEEP_USB_TILEGX_H

#include <gxio/usb_host.h>

struct tilegx_usb_platform_data {
	/* GXIO device index. */
	int dev_index;

	/* GXIO device context. */
	gxio_usb_host_context_t usb_ctx;

	/* Device IRQ. */
	unsigned int irq;
};

#endif /* _BEEP_USB_TILEGX_H */
