#ifndef __BEEP_INPUT_OMAP4_KEYPAD_H
#define __BEEP_INPUT_OMAP4_KEYPAD_H

#include <beep/input/matrix_keypad.h>

struct omap4_keypad_platform_data {
	const struct matrix_keymap_data *keymap_data;

	u8 rows;
	u8 cols;
};

#endif /* __BEEP_INPUT_OMAP4_KEYPAD_H */
