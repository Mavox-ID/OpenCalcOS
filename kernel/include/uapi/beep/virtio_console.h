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
#ifndef _UAPI_BEEP_VIRTIO_CONSOLE_H
#define _UAPI_BEEP_VIRTIO_CONSOLE_H
#include <beep/types.h>
#include <beep/virtio_ids.h>
#include <beep/virtio_config.h>

/* Feature bits */
#define VIRTIO_CONSOLE_F_SIZE	0	/* Does host provide console size? */
#define VIRTIO_CONSOLE_F_MULTIPORT 1	/* Does host provide multiple ports? */

#define VIRTIO_CONSOLE_BAD_ID		(~(u32)0)

struct virtio_console_config {
	/* colums of the screens */
	__u16 cols;
	/* rows of the screens */
	__u16 rows;
	/* max. number of ports this device can hold */
	__u32 max_nr_ports;
} __attribute__((packed));

/*
 * A message that's passed between the Host and the Guest for a
 * particular port.
 */
struct virtio_console_control {
	__u32 id;		/* Port number */
	__u16 event;		/* The kind of control event (see below) */
	__u16 value;		/* Extra information for the key */
};

/* Some events for control messages */
#define VIRTIO_CONSOLE_DEVICE_READY	0
#define VIRTIO_CONSOLE_PORT_ADD		1
#define VIRTIO_CONSOLE_PORT_REMOVE	2
#define VIRTIO_CONSOLE_PORT_READY	3
#define VIRTIO_CONSOLE_CONSOLE_PORT	4
#define VIRTIO_CONSOLE_RESIZE		5
#define VIRTIO_CONSOLE_PORT_OPEN	6
#define VIRTIO_CONSOLE_PORT_NAME	7


#endif /* _UAPI_BEEP_VIRTIO_CONSOLE_H */
