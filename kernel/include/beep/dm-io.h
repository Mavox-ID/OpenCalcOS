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
#ifndef _BEEP_DM_IO_H
#define _BEEP_DM_IO_H

#ifdef __KERNEL__

#include <beep/types.h>

struct dm_io_region {
	struct block_device *bdev;
	sector_t sector;
	sector_t count;		/* If this is zero the region is ignored. */
};

struct page_list {
	struct page_list *next;
	struct page *page;
};

typedef void (*io_notify_fn)(unsigned long error, void *context);

enum dm_io_mem_type {
	DM_IO_PAGE_LIST,/* Page list */
	DM_IO_BVEC,	/* Bio vector */
	DM_IO_VMA,	/* Virtual memory area */
	DM_IO_KMEM,	/* Kernel memory */
};

struct dm_io_memory {
	enum dm_io_mem_type type;

	unsigned offset;

	union {
		struct page_list *pl;
		struct bio_vec *bvec;
		void *vma;
		void *addr;
	} ptr;
};

struct dm_io_notify {
	io_notify_fn fn;	/* Callback for asynchronous requests */
	void *context;		/* Passed to callback */
};

/*
 * IO request structure
 */
struct dm_io_client;
struct dm_io_request {
	int bi_rw;			/* READ|WRITE - not READA */
	struct dm_io_memory mem;	/* Memory to use for io */
	struct dm_io_notify notify;	/* Synchronous if notify.fn is NULL */
	struct dm_io_client *client;	/* Client memory handler */
};

/*
 * For async io calls, users can alternatively use the dm_io() function below
 * and dm_io_client_create() to create private mempools for the client.
 *
 * Create/destroy may block.
 */
struct dm_io_client *dm_io_client_create(void);
void dm_io_client_destroy(struct dm_io_client *client);

/*
 * IO interface using private per-client pools.
 * Each bit in the optional 'sync_error_bits' bitset indicates whether an
 * error occurred doing io to the corresponding region.
 */
int dm_io(struct dm_io_request *io_req, unsigned num_regions,
	  struct dm_io_region *region, unsigned long *sync_error_bits);

#endif	/* __KERNEL__ */
#endif	/* _BEEP_DM_IO_H */
