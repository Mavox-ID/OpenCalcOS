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
#ifndef __BEEP_LM8323_H
#define __BEEP_LM8323_H

#include <beep/types.h>

/*
 * Largest keycode that the chip can send, plus one,
 * so keys can be mapped directly at the index of the
 * LM8323 keycode instead of subtracting one.
 */
#define LM8323_KEYMAP_SIZE	(0x7f + 1)

#define LM8323_NUM_PWMS		3

struct lm8323_platform_data {
	int debounce_time; /* Time to watch for key bouncing, in ms. */
	int active_time; /* Idle time until sleep, in ms. */

	int size_x;
	int size_y;
	bool repeat;
	const unsigned short *keymap;

	const char *pwm_names[LM8323_NUM_PWMS];

	const char *name; /* Device name. */
};

#endif /* __BEEP_LM8323_H */
