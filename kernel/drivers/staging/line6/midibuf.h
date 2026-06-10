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
#ifndef MIDIBUF_H
#define MIDIBUF_H

struct MidiBuffer {
	unsigned char *buf;
	int size;
	int split;
	int pos_read, pos_write;
	int full;
	int command_prev;
};

extern int line6_midibuf_bytes_used(struct MidiBuffer *mb);
extern int line6_midibuf_bytes_free(struct MidiBuffer *mb);
extern void line6_midibuf_destroy(struct MidiBuffer *mb);
extern int line6_midibuf_ignore(struct MidiBuffer *mb, int length);
extern int line6_midibuf_init(struct MidiBuffer *mb, int size, int split);
extern int line6_midibuf_read(struct MidiBuffer *mb, unsigned char *data,
			      int length);
extern void line6_midibuf_reset(struct MidiBuffer *mb);
extern int line6_midibuf_skip_message(struct MidiBuffer *mb,
				      unsigned short mask);
extern void line6_midibuf_status(struct MidiBuffer *mb);
extern int line6_midibuf_write(struct MidiBuffer *mb, unsigned char *data,
			       int length);

#endif
