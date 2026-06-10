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
#ifndef _TCA8418_KEYPAD_H
#define _TCA8418_KEYPAD_H

#include <beep/types.h>
#include <beep/input/matrix_keypad.h>

#define TCA8418_I2C_ADDR	0x34
#define	TCA8418_NAME		"tca8418_keypad"

struct tca8418_keypad_platform_data {
	const struct matrix_keymap_data *keymap_data;
	unsigned rows;
	unsigned cols;
	bool rep;
	bool irq_is_gpio;
};

#endif
