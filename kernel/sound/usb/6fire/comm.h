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
#ifndef USB6FIRE_COMM_H
#define USB6FIRE_COMM_H

#include "common.h"

enum /* settings for comm */
{
	COMM_RECEIVER_BUFSIZE = 64,
};

struct comm_runtime {
	struct sfire_chip *chip;

	struct urb receiver;
	u8 receiver_buffer[COMM_RECEIVER_BUFSIZE];

	u8 serial; /* urb serial */

	void (*init_urb)(struct comm_runtime *rt, struct urb *urb, u8 *buffer,
			void *context, void(*handler)(struct urb *urb));
	/* writes control data to the device */
	int (*write8)(struct comm_runtime *rt, u8 request, u8 reg, u8 value);
	int (*write16)(struct comm_runtime *rt, u8 request, u8 reg,
			u8 vh, u8 vl);
};

int usb6fire_comm_init(struct sfire_chip *chip);
void usb6fire_comm_abort(struct sfire_chip *chip);
void usb6fire_comm_destroy(struct sfire_chip *chip);
#endif /* USB6FIRE_COMM_H */

