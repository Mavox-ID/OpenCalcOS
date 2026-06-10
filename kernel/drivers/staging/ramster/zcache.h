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
#ifndef _ZCACHE_H_
#define _ZCACHE_H_

struct zcache_preload {
	struct tmem_obj *obj;
	struct tmem_objnode *objnodes[OBJNODE_TREE_MAX_PATH];
};

struct tmem_pool;

#define MAX_POOLS_PER_CLIENT 16

#define MAX_CLIENTS 16
#define LOCAL_CLIENT ((uint16_t)-1)

struct zcache_client {
	struct tmem_pool *tmem_pools[MAX_POOLS_PER_CLIENT];
	bool allocated;
	atomic_t refcount;
};

extern struct tmem_pool *zcache_get_pool_by_id(uint16_t cli_id,
							uint16_t poolid);
extern void zcache_put_pool(struct tmem_pool *pool);

extern int zcache_put_page(int, int, struct tmem_oid *,
				uint32_t, void *,
				unsigned int, bool, int);
extern int zcache_get_page(int, int, struct tmem_oid *, uint32_t,
				void *, size_t *, bool, int);
extern int zcache_flush_page(int, int, struct tmem_oid *, uint32_t);
extern int zcache_flush_object(int, int, struct tmem_oid *);
extern void zcache_decompress_to_page(char *, unsigned int, struct page *);

#ifdef CONFIG_RAMSTER
extern void *zcache_pampd_create(char *, unsigned int, bool, int,
				struct tmem_handle *);
int zcache_autocreate_pool(unsigned int cli_id, unsigned int pool_id, bool eph);
#endif

#define MAX_POOLS_PER_CLIENT 16

#define MAX_CLIENTS 16
#define LOCAL_CLIENT ((uint16_t)-1)

#endif /* _ZCACHE_H_ */
