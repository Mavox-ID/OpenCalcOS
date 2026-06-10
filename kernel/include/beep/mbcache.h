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
struct mb_cache_entry {
	struct list_head		e_lru_list;
	struct mb_cache			*e_cache;
	unsigned short			e_used;
	unsigned short			e_queued;
	struct block_device		*e_bdev;
	sector_t			e_block;
	struct list_head		e_block_list;
	struct {
		struct list_head	o_list;
		unsigned int		o_key;
	} e_index;
};

struct mb_cache {
	struct list_head		c_cache_list;
	const char			*c_name;
	atomic_t			c_entry_count;
	int				c_max_entries;
	int				c_bucket_bits;
	struct kmem_cache		*c_entry_cache;
	struct list_head		*c_block_hash;
	struct list_head		*c_index_hash;
};

/* Functions on caches */

struct mb_cache *mb_cache_create(const char *, int);
void mb_cache_shrink(struct block_device *);
void mb_cache_destroy(struct mb_cache *);

/* Functions on cache entries */

struct mb_cache_entry *mb_cache_entry_alloc(struct mb_cache *, gfp_t);
int mb_cache_entry_insert(struct mb_cache_entry *, struct block_device *,
			  sector_t, unsigned int);
void mb_cache_entry_release(struct mb_cache_entry *);
void mb_cache_entry_free(struct mb_cache_entry *);
struct mb_cache_entry *mb_cache_entry_get(struct mb_cache *,
					  struct block_device *,
					  sector_t);
struct mb_cache_entry *mb_cache_entry_find_first(struct mb_cache *cache,
						 struct block_device *, 
						 unsigned int);
struct mb_cache_entry *mb_cache_entry_find_next(struct mb_cache_entry *,
						struct block_device *, 
						unsigned int);
