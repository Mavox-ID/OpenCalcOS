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
#ifndef GH_
#define GH_
#include <dspbridge/host_os.h>

extern struct gh_t_hash_tab *gh_create(u16 max_bucket, u16 val_size,
				       u16(*hash) (void *, u16),
				       bool(*match) (void *, void *),
				       void (*delete) (void *));
extern void gh_delete(struct gh_t_hash_tab *hash_tab);
extern void *gh_find(struct gh_t_hash_tab *hash_tab, void *key);
extern void *gh_insert(struct gh_t_hash_tab *hash_tab, void *key, void *value);
#ifdef CONFIG_TIDSPBRIDGE_BACKTRACE
void gh_iterate(struct gh_t_hash_tab *hash_tab,
	void (*callback)(void *, void *), void *user_data);
#endif
#endif /* GH_ */
