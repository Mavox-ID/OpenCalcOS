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
#ifndef __BEEP_MCS_H
#define __BEEP_MCS_H

#define MCS_KEY_MAP(v, c)	((((v) & 0xff) << 16) | ((c) & 0xffff))
#define MCS_KEY_VAL(v)		(((v) >> 16) & 0xff)
#define MCS_KEY_CODE(v)		((v) & 0xffff)

struct mcs_platform_data {
	void (*poweron)(bool);
	void (*cfg_pin)(void);

	/* touchscreen */
	unsigned int x_size;
	unsigned int y_size;

	/* touchkey */
	const u32 *keymap;
	unsigned int keymap_size;
	unsigned int key_maxval;
	bool no_autorepeat;
};

#endif	/* __BEEP_MCS_H */
