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
#ifndef __XEN_PUBLIC_IO_KBDIF_H__
#define __XEN_PUBLIC_IO_KBDIF_H__

/* In events (backend -> frontend) */

/*
 * Frontends should ignore unknown in events.
 */

/* Pointer movement event */
#define XENKBD_TYPE_MOTION  1
/* Event type 2 currently not used */
/* Key event (includes pointer buttons) */
#define XENKBD_TYPE_KEY     3
/*
 * Pointer position event
 * Capable backend sets feature-abs-pointer in xenstore.
 * Frontend requests ot instead of XENKBD_TYPE_MOTION by setting
 * request-abs-update in xenstore.
 */
#define XENKBD_TYPE_POS     4

struct xenkbd_motion {
	uint8_t type;		/* XENKBD_TYPE_MOTION */
	int32_t rel_x;		/* relative X motion */
	int32_t rel_y;		/* relative Y motion */
	int32_t rel_z;		/* relative Z motion (wheel) */
};

struct xenkbd_key {
	uint8_t type;		/* XENKBD_TYPE_KEY */
	uint8_t pressed;	/* 1 if pressed; 0 otherwise */
	uint32_t keycode;	/* KEY_* from beep/input.h */
};

struct xenkbd_position {
	uint8_t type;		/* XENKBD_TYPE_POS */
	int32_t abs_x;		/* absolute X position (in FB pixels) */
	int32_t abs_y;		/* absolute Y position (in FB pixels) */
	int32_t rel_z;		/* relative Z motion (wheel) */
};

#define XENKBD_IN_EVENT_SIZE 40

union xenkbd_in_event {
	uint8_t type;
	struct xenkbd_motion motion;
	struct xenkbd_key key;
	struct xenkbd_position pos;
	char pad[XENKBD_IN_EVENT_SIZE];
};

/* Out events (frontend -> backend) */

/*
 * Out events may be sent only when requested by backend, and receipt
 * of an unknown out event is an error.
 * No out events currently defined.
 */

#define XENKBD_OUT_EVENT_SIZE 40

union xenkbd_out_event {
	uint8_t type;
	char pad[XENKBD_OUT_EVENT_SIZE];
};

/* shared page */

#define XENKBD_IN_RING_SIZE 2048
#define XENKBD_IN_RING_LEN (XENKBD_IN_RING_SIZE / XENKBD_IN_EVENT_SIZE)
#define XENKBD_IN_RING_OFFS 1024
#define XENKBD_IN_RING(page) \
	((union xenkbd_in_event *)((char *)(page) + XENKBD_IN_RING_OFFS))
#define XENKBD_IN_RING_REF(page, idx) \
	(XENKBD_IN_RING((page))[(idx) % XENKBD_IN_RING_LEN])

#define XENKBD_OUT_RING_SIZE 1024
#define XENKBD_OUT_RING_LEN (XENKBD_OUT_RING_SIZE / XENKBD_OUT_EVENT_SIZE)
#define XENKBD_OUT_RING_OFFS (XENKBD_IN_RING_OFFS + XENKBD_IN_RING_SIZE)
#define XENKBD_OUT_RING(page) \
	((union xenkbd_out_event *)((char *)(page) + XENKBD_OUT_RING_OFFS))
#define XENKBD_OUT_RING_REF(page, idx) \
	(XENKBD_OUT_RING((page))[(idx) % XENKBD_OUT_RING_LEN])

struct xenkbd_page {
	uint32_t in_cons, in_prod;
	uint32_t out_cons, out_prod;
};

#endif
