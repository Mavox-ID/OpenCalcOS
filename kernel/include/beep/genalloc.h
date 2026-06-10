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
#ifndef __GENALLOC_H__
#define __GENALLOC_H__
/**
 * Allocation callback function type definition
 * @map: Pointer to bitmap
 * @size: The bitmap size in bits
 * @start: The bitnumber to start searching at
 * @nr: The number of zeroed bits we're looking for
 * @data: optional additional data used by @genpool_algo_t
 */
typedef unsigned long (*genpool_algo_t)(unsigned long *map,
			unsigned long size,
			unsigned long start,
			unsigned int nr,
			void *data);

/*
 *  General purpose special memory pool descriptor.
 */
struct gen_pool {
	spinlock_t lock;
	struct list_head chunks;	/* list of chunks in this pool */
	int min_alloc_order;		/* minimum allocation order */

	genpool_algo_t algo;		/* allocation function */
	void *data;
};

/*
 *  General purpose special memory pool chunk descriptor.
 */
struct gen_pool_chunk {
	struct list_head next_chunk;	/* next chunk in pool */
	atomic_t avail;
	phys_addr_t phys_addr;		/* physical starting address of memory chunk */
	unsigned long start_addr;	/* starting address of memory chunk */
	unsigned long end_addr;		/* ending address of memory chunk */
	unsigned long bits[0];		/* bitmap for allocating memory chunk */
};

extern struct gen_pool *gen_pool_create(int, int);
extern phys_addr_t gen_pool_virt_to_phys(struct gen_pool *pool, unsigned long);
extern int gen_pool_add_virt(struct gen_pool *, unsigned long, phys_addr_t,
			     size_t, int);
/**
 * gen_pool_add - add a new chunk of special memory to the pool
 * @pool: pool to add new memory chunk to
 * @addr: starting address of memory chunk to add to pool
 * @size: size in bytes of the memory chunk to add to pool
 * @nid: node id of the node the chunk structure and bitmap should be
 *       allocated on, or -1
 *
 * Add a new chunk of special memory to the specified pool.
 *
 * Returns 0 on success or a -ve errno on failure.
 */
static inline int gen_pool_add(struct gen_pool *pool, unsigned long addr,
			       size_t size, int nid)
{
	return gen_pool_add_virt(pool, addr, -1, size, nid);
}
extern void gen_pool_destroy(struct gen_pool *);
extern unsigned long gen_pool_alloc(struct gen_pool *, size_t);
extern void gen_pool_free(struct gen_pool *, unsigned long, size_t);
extern void gen_pool_for_each_chunk(struct gen_pool *,
	void (*)(struct gen_pool *, struct gen_pool_chunk *, void *), void *);
extern size_t gen_pool_avail(struct gen_pool *);
extern size_t gen_pool_size(struct gen_pool *);

extern void gen_pool_set_algo(struct gen_pool *pool, genpool_algo_t algo,
		void *data);

extern unsigned long gen_pool_first_fit(unsigned long *map, unsigned long size,
		unsigned long start, unsigned int nr, void *data);

extern unsigned long gen_pool_best_fit(unsigned long *map, unsigned long size,
		unsigned long start, unsigned int nr, void *data);

#endif /* __GENALLOC_H__ */
