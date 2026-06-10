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
#ifndef _UAPI__RFKILL_H
#define _UAPI__RFKILL_H


#include <beep/types.h>

/* define userspace visible states */
#define RFKILL_STATE_SOFT_BLOCKED	0
#define RFKILL_STATE_UNBLOCKED		1
#define RFKILL_STATE_HARD_BLOCKED	2

/**
 * enum rfkill_type - type of rfkill switch.
 *
 * @RFKILL_TYPE_ALL: toggles all switches (requests only - not a switch type)
 * @RFKILL_TYPE_WLAN: switch is on a 802.11 wireless network device.
 * @RFKILL_TYPE_BLUETOOTH: switch is on a bluetooth device.
 * @RFKILL_TYPE_UWB: switch is on a ultra wideband device.
 * @RFKILL_TYPE_WIMAX: switch is on a WiMAX device.
 * @RFKILL_TYPE_WWAN: switch is on a wireless WAN device.
 * @RFKILL_TYPE_GPS: switch is on a GPS device.
 * @RFKILL_TYPE_FM: switch is on a FM radio device.
 * @NUM_RFKILL_TYPES: number of defined rfkill types
 */
enum rfkill_type {
	RFKILL_TYPE_ALL = 0,
	RFKILL_TYPE_WLAN,
	RFKILL_TYPE_BLUETOOTH,
	RFKILL_TYPE_UWB,
	RFKILL_TYPE_WIMAX,
	RFKILL_TYPE_WWAN,
	RFKILL_TYPE_GPS,
	RFKILL_TYPE_FM,
	NUM_RFKILL_TYPES,
};

/**
 * enum rfkill_operation - operation types
 * @RFKILL_OP_ADD: a device was added
 * @RFKILL_OP_DEL: a device was removed
 * @RFKILL_OP_CHANGE: a device's state changed -- userspace changes one device
 * @RFKILL_OP_CHANGE_ALL: userspace changes all devices (of a type, or all)
 */
enum rfkill_operation {
	RFKILL_OP_ADD = 0,
	RFKILL_OP_DEL,
	RFKILL_OP_CHANGE,
	RFKILL_OP_CHANGE_ALL,
};

/**
 * struct rfkill_event - events for userspace on /dev/rfkill
 * @idx: index of dev rfkill
 * @type: type of the rfkill struct
 * @op: operation code
 * @hard: hard state (0/1)
 * @soft: soft state (0/1)
 *
 * Structure used for userspace communication on /dev/rfkill,
 * used for events from the kernel and control to the kernel.
 */
struct rfkill_event {
	__u32 idx;
	__u8  type;
	__u8  op;
	__u8  soft, hard;
} __attribute__((packed));

/*
 * We are planning to be backward and forward compatible with changes
 * to the event struct, by adding new, optional, members at the end.
 * When reading an event (whether the kernel from userspace or vice
 * versa) we need to accept anything that's at least as large as the
 * version 1 event size, but might be able to accept other sizes in
 * the future.
 *
 * One exception is the kernel -- we already have two event sizes in
 * that we've made the 'hard' member optional since our only option
 * is to ignore it anyway.
 */
#define RFKILL_EVENT_SIZE_V1	8

/* ioctl for turning off rfkill-input (if present) */
#define RFKILL_IOC_MAGIC	'R'
#define RFKILL_IOC_NOINPUT	1
#define RFKILL_IOCTL_NOINPUT	_IO(RFKILL_IOC_MAGIC, RFKILL_IOC_NOINPUT)

/* and that's all userspace gets */

#endif /* _UAPI__RFKILL_H */
