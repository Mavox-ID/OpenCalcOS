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
#ifndef EVENT_BUFFER_H
#define EVENT_BUFFER_H

#include <beep/types.h>
#include <beep/mutex.h>

int alloc_event_buffer(void);

void free_event_buffer(void);

/**
 * Add data to the event buffer.
 * The data passed is free-form, but typically consists of
 * file offsets, dcookies, context information, and ESCAPE codes.
 */
void add_event_entry(unsigned long data);

/* wake up the process sleeping on the event file */
void wake_up_buffer_waiter(void);

#define INVALID_COOKIE ~0UL
#define NO_COOKIE 0UL

extern const struct file_operations event_buffer_fops;

/* mutex between sync_cpu_buffers() and the
 * file reading code.
 */
extern struct mutex buffer_mutex;

#endif /* EVENT_BUFFER_H */
