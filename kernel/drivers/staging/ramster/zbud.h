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
#ifndef _ZBUD_H_
#define _ZBUD_H_

#include "tmem.h"

struct zbudref;

extern unsigned int zbud_max_buddy_size(void);
extern struct zbudref *zbud_match_prep(struct tmem_handle *th, bool eph,
						void *cdata, unsigned size);
extern struct zbudref *zbud_create_prep(struct tmem_handle *th, bool eph,
						void *cdata, unsigned size,
						struct page *newpage);
extern void zbud_create_finish(struct zbudref *, bool);
extern int zbud_decompress(struct page *, struct zbudref *, bool,
				void (*func)(char *, unsigned int, char *));
extern int zbud_copy_from_zbud(char *, struct zbudref *, size_t *, bool);
extern int zbud_copy_to_zbud(struct zbudref *, char *, bool);
extern struct page *zbud_free_and_delist(struct zbudref *, bool eph,
						unsigned int *, unsigned int *);
extern struct page *zbud_evict_pageframe_lru(unsigned int *, unsigned int *);
extern unsigned int zbud_make_zombie_lru(struct tmem_handle *, unsigned char **,
						unsigned int *, bool);
extern void zbud_init(void);

#endif /* _ZBUD_H_ */
