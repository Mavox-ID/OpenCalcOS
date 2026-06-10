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
#ifndef USB6FIRE_MIDI_H
#define USB6FIRE_MIDI_H

#include "common.h"

enum {
	MIDI_BUFSIZE = 64
};

struct midi_runtime {
	struct sfire_chip *chip;
	struct snd_rawmidi *instance;

	struct snd_rawmidi_substream *in;
	char in_active;

	spinlock_t in_lock;
	spinlock_t out_lock;
	struct snd_rawmidi_substream *out;
	struct urb out_urb;
	u8 out_serial; /* serial number of out packet */
	u8 out_buffer[MIDI_BUFSIZE];
	int buffer_offset;

	void (*in_received)(struct midi_runtime *rt, u8 *data, int length);
};

int usb6fire_midi_init(struct sfire_chip *chip);
void usb6fire_midi_abort(struct sfire_chip *chip);
void usb6fire_midi_destroy(struct sfire_chip *chip);
#endif /* USB6FIRE_MIDI_H */

