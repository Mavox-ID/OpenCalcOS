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
#ifndef COH901318_LLI_H
#define COH901318_LLI_H

#include <mach/coh901318.h>

struct device;

struct coh901318_pool {
	spinlock_t lock;
	struct dma_pool *dmapool;
	struct device *dev;

#ifdef CONFIG_DEBUG_FS
	int debugfs_pool_counter;
#endif
};

struct device;
/**
 * coh901318_pool_create() - Creates an dma pool for lli:s
 * @pool: pool handle
 * @dev: dma device
 * @lli_nbr: number of lli:s in the pool
 * @algin: address alignemtn of lli:s
 * returns 0 on success otherwise none zero
 */
int coh901318_pool_create(struct coh901318_pool *pool,
			  struct device *dev,
			  size_t lli_nbr, size_t align);

/**
 * coh901318_pool_destroy() - Destroys the dma pool
 * @pool: pool handle
 * returns 0 on success otherwise none zero
 */
int coh901318_pool_destroy(struct coh901318_pool *pool);

/**
 * coh901318_lli_alloc() - Allocates a linked list
 *
 * @pool: pool handle
 * @len: length to list
 * return: none NULL if success otherwise NULL
 */
struct coh901318_lli *
coh901318_lli_alloc(struct coh901318_pool *pool,
		    unsigned int len);

/**
 * coh901318_lli_free() - Returns the linked list items to the pool
 * @pool: pool handle
 * @lli: reference to lli pointer to be freed
 */
void coh901318_lli_free(struct coh901318_pool *pool,
			struct coh901318_lli **lli);

/**
 * coh901318_lli_fill_memcpy() - Prepares the lli:s for dma memcpy
 * @pool: pool handle
 * @lli: allocated lli
 * @src: src address
 * @size: transfer size
 * @dst: destination address
 * @ctrl_chained: ctrl for chained lli
 * @ctrl_last: ctrl for the last lli
 * returns number of CPU interrupts for the lli, negative on error.
 */
int
coh901318_lli_fill_memcpy(struct coh901318_pool *pool,
			  struct coh901318_lli *lli,
			  dma_addr_t src, unsigned int size,
			  dma_addr_t dst, u32 ctrl_chained, u32 ctrl_last);

/**
 * coh901318_lli_fill_single() - Prepares the lli:s for dma single transfer
 * @pool: pool handle
 * @lli: allocated lli
 * @buf: transfer buffer
 * @size: transfer size
 * @dev_addr: address of periphal
 * @ctrl_chained: ctrl for chained lli
 * @ctrl_last: ctrl for the last lli
 * @dir: direction of transfer (to or from device)
 * returns number of CPU interrupts for the lli, negative on error.
 */
int
coh901318_lli_fill_single(struct coh901318_pool *pool,
			  struct coh901318_lli *lli,
			  dma_addr_t buf, unsigned int size,
			  dma_addr_t dev_addr, u32 ctrl_chained, u32 ctrl_last,
			  enum dma_transfer_direction dir);

/**
 * coh901318_lli_fill_single() - Prepares the lli:s for dma scatter list transfer
 * @pool: pool handle
 * @lli: allocated lli
 * @sg: scatter gather list
 * @nents: number of entries in sg
 * @dev_addr: address of periphal
 * @ctrl_chained: ctrl for chained lli
 * @ctrl: ctrl of middle lli
 * @ctrl_last: ctrl for the last lli
 * @dir: direction of transfer (to or from device)
 * @ctrl_irq_mask: ctrl mask for CPU interrupt
 * returns number of CPU interrupts for the lli, negative on error.
 */
int
coh901318_lli_fill_sg(struct coh901318_pool *pool,
		      struct coh901318_lli *lli,
		      struct scatterlist *sg, unsigned int nents,
		      dma_addr_t dev_addr, u32 ctrl_chained,
		      u32 ctrl, u32 ctrl_last,
		      enum dma_transfer_direction dir, u32 ctrl_irq_mask);

#endif /* COH901318_LLI_H */
