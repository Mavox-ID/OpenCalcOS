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
#if !defined(IB_FMR_POOL_H)
#define IB_FMR_POOL_H

#include <rdma/ib_verbs.h>

struct ib_fmr_pool;

/**
 * struct ib_fmr_pool_param - Parameters for creating FMR pool
 * @max_pages_per_fmr:Maximum number of pages per map request.
 * @page_shift: Log2 of sizeof "pages" mapped by this fmr
 * @access:Access flags for FMRs in pool.
 * @pool_size:Number of FMRs to allocate for pool.
 * @dirty_watermark:Flush is triggered when @dirty_watermark dirty
 *     FMRs are present.
 * @flush_function:Callback called when unmapped FMRs are flushed and
 *     more FMRs are possibly available for mapping
 * @flush_arg:Context passed to user's flush function.
 * @cache:If set, FMRs may be reused after unmapping for identical map
 *     requests.
 */
struct ib_fmr_pool_param {
	int                     max_pages_per_fmr;
	int                     page_shift;
	enum ib_access_flags    access;
	int                     pool_size;
	int                     dirty_watermark;
	void                  (*flush_function)(struct ib_fmr_pool *pool,
						void               *arg);
	void                   *flush_arg;
	unsigned                cache:1;
};

struct ib_pool_fmr {
	struct ib_fmr      *fmr;
	struct ib_fmr_pool *pool;
	struct list_head    list;
	struct hlist_node   cache_node;
	int                 ref_count;
	int                 remap_count;
	u64                 io_virtual_address;
	int                 page_list_len;
	u64                 page_list[0];
};

struct ib_fmr_pool *ib_create_fmr_pool(struct ib_pd             *pd,
				       struct ib_fmr_pool_param *params);

void ib_destroy_fmr_pool(struct ib_fmr_pool *pool);

int ib_flush_fmr_pool(struct ib_fmr_pool *pool);

struct ib_pool_fmr *ib_fmr_pool_map_phys(struct ib_fmr_pool *pool_handle,
					 u64                *page_list,
					 int                 list_len,
					 u64                 io_virtual_address);

int ib_fmr_pool_unmap(struct ib_pool_fmr *fmr);

#endif /* IB_FMR_POOL_H */
