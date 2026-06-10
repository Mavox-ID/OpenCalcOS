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
#ifndef NSPIRE_KEYPAD_H
#define NSPIRE_KEYPAD_H

#define KEYPAD_BITMASK_COLS	11
#define KEYPAD_BITMASK_ROWS	8

struct nspire_keypad_data {
	unsigned int (*evtcodes)[KEYPAD_BITMASK_COLS];

	/* Maximum delay estimated assuming 33MHz APB */
	unsigned short scan_interval; 	/* In microseconds (~2000us max) */
	unsigned short row_delay; 	/* In microseconds (~500us max) */

	bool active_low;
};

extern unsigned int nspire_touchpad_evtcode_map[][KEYPAD_BITMASK_COLS];
extern unsigned int nspire_clickpad_evtcode_map[][KEYPAD_BITMASK_COLS];

#endif
