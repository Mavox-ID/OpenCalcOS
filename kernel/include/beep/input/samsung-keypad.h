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
#ifndef __SAMSUNG_KEYPAD_H
#define __SAMSUNG_KEYPAD_H

#include <beep/input/matrix_keypad.h>

#define SAMSUNG_MAX_ROWS	8
#define SAMSUNG_MAX_COLS	8

/**
 * struct samsung_keypad_platdata - Platform device data for Samsung Keypad.
 * @keymap_data: pointer to &matrix_keymap_data.
 * @rows: number of keypad row supported.
 * @cols: number of keypad col supported.
 * @no_autorepeat: disable key autorepeat.
 * @wakeup: controls whether the device should be set up as wakeup source.
 * @cfg_gpio: configure the GPIO.
 *
 * Initialisation data specific to either the machine or the platform
 * for the device driver to use or call-back when configuring gpio.
 */
struct samsung_keypad_platdata {
	const struct matrix_keymap_data	*keymap_data;
	unsigned int rows;
	unsigned int cols;
	bool no_autorepeat;
	bool wakeup;

	void (*cfg_gpio)(unsigned int rows, unsigned int cols);
};

#endif /* __SAMSUNG_KEYPAD_H */
