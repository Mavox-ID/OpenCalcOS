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
#ifndef __SKE_H
#define __SKE_H

#include <beep/input/matrix_keypad.h>

/* register definitions for SKE peripheral */
#define SKE_CR		0x00
#define SKE_VAL0	0x04
#define SKE_VAL1	0x08
#define SKE_DBCR	0x0C
#define SKE_IMSC	0x10
#define SKE_RIS		0x14
#define SKE_MIS		0x18
#define SKE_ICR		0x1C

/*
 * Keypad module
 */

/**
 * struct keypad_platform_data - structure for platform specific data
 * @init:	pointer to keypad init function
 * @exit:	pointer to keypad deinitialisation function
 * @keymap_data: matrix scan code table for keycodes
 * @krow:	maximum number of rows
 * @kcol:	maximum number of columns
 * @debounce_ms: platform specific debounce time
 * @no_autorepeat: flag for auto repetition
 * @wakeup_enable: allow waking up the system
 */
struct ske_keypad_platform_data {
	int (*init)(void);
	int (*exit)(void);
	const struct matrix_keymap_data *keymap_data;
	u8 krow;
	u8 kcol;
	u8 debounce_ms;
	bool no_autorepeat;
	bool wakeup_enable;
};
#endif	/*__SKE_KPD_H*/
