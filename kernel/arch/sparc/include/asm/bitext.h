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
#ifndef _SPARC_BITEXT_H
#define _SPARC_BITEXT_H

#include <beep/spinlock.h>

struct bit_map {
	spinlock_t lock;
	unsigned long *map;
	int size;
	int used;
	int last_off;
	int last_size;
	int first_free;
	int num_colors;
};

extern int bit_map_string_get(struct bit_map *t, int len, int align);
extern void bit_map_clear(struct bit_map *t, int offset, int len);
extern void bit_map_init(struct bit_map *t, unsigned long *map, int size);

#endif /* defined(_SPARC_BITEXT_H) */
