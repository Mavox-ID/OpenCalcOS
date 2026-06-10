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
#ifndef TTM_PAGE_ALLOC
#define TTM_PAGE_ALLOC

#include <drm/ttm/ttm_bo_driver.h>
#include <drm/ttm/ttm_memory.h>

/**
 * Initialize pool allocator.
 */
int ttm_page_alloc_init(struct ttm_mem_global *glob, unsigned max_pages);
/**
 * Free pool allocator.
 */
void ttm_page_alloc_fini(void);

/**
 * ttm_pool_populate:
 *
 * @ttm: The struct ttm_tt to contain the backing pages.
 *
 * Add backing pages to all of @ttm
 */
extern int ttm_pool_populate(struct ttm_tt *ttm);

/**
 * ttm_pool_unpopulate:
 *
 * @ttm: The struct ttm_tt which to free backing pages.
 *
 * Free all pages of @ttm
 */
extern void ttm_pool_unpopulate(struct ttm_tt *ttm);

/**
 * Output the state of pools to debugfs file
 */
extern int ttm_page_alloc_debugfs(struct seq_file *m, void *data);


#ifdef CONFIG_SWIOTLB
/**
 * Initialize pool allocator.
 */
int ttm_dma_page_alloc_init(struct ttm_mem_global *glob, unsigned max_pages);

/**
 * Free pool allocator.
 */
void ttm_dma_page_alloc_fini(void);

/**
 * Output the state of pools to debugfs file
 */
extern int ttm_dma_page_alloc_debugfs(struct seq_file *m, void *data);

extern int ttm_dma_populate(struct ttm_dma_tt *ttm_dma, struct device *dev);
extern void ttm_dma_unpopulate(struct ttm_dma_tt *ttm_dma, struct device *dev);

#else
static inline int ttm_dma_page_alloc_init(struct ttm_mem_global *glob,
					  unsigned max_pages)
{
	return -ENODEV;
}

static inline void ttm_dma_page_alloc_fini(void) { return; }

static inline int ttm_dma_page_alloc_debugfs(struct seq_file *m, void *data)
{
	return 0;
}
#endif

#endif
