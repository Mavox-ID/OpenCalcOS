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
#ifndef __BEEP_USB_GADGETFS_H
#define __BEEP_USB_GADGETFS_H

#include <beep/types.h>
#include <beep/ioctl.h>

#include <beep/usb/ch9.h>

/*
 * Events are delivered on the ep0 file descriptor, when the user mode driver
 * reads from this file descriptor after writing the descriptors.  Don't
 * stop polling this descriptor.
 */

enum usb_gadgetfs_event_type {
	GADGETFS_NOP = 0,

	GADGETFS_CONNECT,
	GADGETFS_DISCONNECT,
	GADGETFS_SETUP,
	GADGETFS_SUSPEND,
	/* and likely more ! */
};

/* NOTE:  this structure must stay the same size and layout on
 * both 32-bit and 64-bit kernels.
 */
struct usb_gadgetfs_event {
	union {
		/* NOP, DISCONNECT, SUSPEND: nothing
		 * ... some hardware can't report disconnection
		 */

		/* CONNECT: just the speed */
		enum usb_device_speed	speed;

		/* SETUP: packet; DATA phase i/o precedes next event
		 *(setup.bmRequestType & USB_DIR_IN) flags direction
		 * ... includes SET_CONFIGURATION, SET_INTERFACE
		 */
		struct usb_ctrlrequest	setup;
	} u;
	enum usb_gadgetfs_event_type	type;
};


/* The 'g' code is also used by printer gadget ioctl requests.
 * Don't add any colliding codes to either driver, and keep
 * them in unique ranges (size 0x20 for now).
 */

/* endpoint ioctls */

/* IN transfers may be reported to the gadget driver as complete
 *	when the fifo is loaded, before the host reads the data;
 * OUT transfers may be reported to the host's "client" driver as
 *	complete when they're sitting in the FIFO unread.
 * THIS returns how many bytes are "unclaimed" in the endpoint fifo
 * (needed for precise fault handling, when the hardware allows it)
 */
#define	GADGETFS_FIFO_STATUS	_IO('g', 1)

/* discards any unclaimed data in the fifo. */
#define	GADGETFS_FIFO_FLUSH	_IO('g', 2)

/* resets endpoint halt+toggle; used to implement set_interface.
 * some hardware (like pxa2xx) can't support this.
 */
#define	GADGETFS_CLEAR_HALT	_IO('g', 3)

#endif /* __BEEP_USB_GADGETFS_H */
