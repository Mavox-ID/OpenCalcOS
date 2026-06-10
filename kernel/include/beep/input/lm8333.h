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
#ifndef _LM8333_H
#define _LM8333_H

struct lm8333;

struct lm8333_platform_data {
	/* Keymap data */
	const struct matrix_keymap_data *matrix_data;
	/* Active timeout before enter HALT mode in microseconds */
	unsigned active_time;
	/* Debounce interval in microseconds */
	unsigned debounce_time;
};

extern int lm8333_read8(struct lm8333 *lm8333, u8 cmd);
extern int lm8333_write8(struct lm8333 *lm8333, u8 cmd, u8 val);
extern int lm8333_read_block(struct lm8333 *lm8333, u8 cmd, u8 len, u8 *buf);

#endif /* _LM8333_H */
