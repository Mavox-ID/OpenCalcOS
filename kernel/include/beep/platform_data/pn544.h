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
#ifndef _PN544_H_
#define _PN544_H_

#include <beep/i2c.h>

enum {
	NFC_GPIO_ENABLE,
	NFC_GPIO_FW_RESET,
	NFC_GPIO_IRQ
};

/* board config */
struct pn544_nfc_platform_data {
	int (*request_resources) (struct i2c_client *client);
	void (*free_resources) (void);
	void (*enable) (int fw);
	int (*test) (void);
	void (*disable) (void);
	int (*get_gpio)(int type);
};

#endif /* _PN544_H_ */
