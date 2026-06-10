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
#ifndef __ASM_ARCH_EP93XX_KEYPAD_H
#define __ASM_ARCH_EP93XX_KEYPAD_H

struct matrix_keymap_data;

/* flags for the ep93xx_keypad driver */
#define EP93XX_KEYPAD_DISABLE_3_KEY	(1<<0)	/* disable 3-key reset */
#define EP93XX_KEYPAD_DIAG_MODE		(1<<1)	/* diagnostic mode */
#define EP93XX_KEYPAD_BACK_DRIVE	(1<<2)	/* back driving mode */
#define EP93XX_KEYPAD_TEST_MODE		(1<<3)	/* scan only column 0 */
#define EP93XX_KEYPAD_KDIV		(1<<4)	/* 1/4 clock or 1/16 clock */
#define EP93XX_KEYPAD_AUTOREPEAT	(1<<5)	/* enable key autorepeat */

/**
 * struct ep93xx_keypad_platform_data - platform specific device structure
 * @keymap_data:	pointer to &matrix_keymap_data
 * @debounce:		debounce start count; terminal count is 0xff
 * @prescale:		row/column counter pre-scaler load value
 * @flags:		see above
 */
struct ep93xx_keypad_platform_data {
	struct matrix_keymap_data *keymap_data;
	unsigned int	debounce;
	unsigned int	prescale;
	unsigned int	flags;
};

#define EP93XX_MATRIX_ROWS		(8)
#define EP93XX_MATRIX_COLS		(8)

#endif	/* __ASM_ARCH_EP93XX_KEYPAD_H */
