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
#ifndef _ZS_MALLOC_H_
#define _ZS_MALLOC_H_

#include <beep/types.h>

/*
 * zsmalloc mapping modes
 *
 * NOTE: These only make a difference when a mapped object spans pages
*/
enum zs_mapmode {
	ZS_MM_RW, /* normal read-write mapping */
	ZS_MM_RO, /* read-only (no copy-out at unmap time) */
	ZS_MM_WO /* write-only (no copy-in at map time) */
};

struct zs_pool;

struct zs_pool *zs_create_pool(const char *name, gfp_t flags);
void zs_destroy_pool(struct zs_pool *pool);

unsigned long zs_malloc(struct zs_pool *pool, size_t size);
void zs_free(struct zs_pool *pool, unsigned long obj);

void *zs_map_object(struct zs_pool *pool, unsigned long handle,
			enum zs_mapmode mm);
void zs_unmap_object(struct zs_pool *pool, unsigned long handle);

u64 zs_get_total_size_bytes(struct zs_pool *pool);

#endif
