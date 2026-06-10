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
#ifndef _VIDEOBUF_DMA_SG_H
#define _VIDEOBUF_DMA_SG_H

#include <media/videobuf-core.h>

/* --------------------------------------------------------------------- */

/*
 * A small set of helper functions to manage buffers (both userland
 * and kernel) for DMA.
 *
 * videobuf_dma_init_*()
 *	creates a buffer.  The userland version takes a userspace
 *	pointer + length.  The kernel version just wants the size and
 *	does memory allocation too using vmalloc_32().
 *
 * videobuf_dma_*()
 *	see Documentation/DMA-API-HOWTO.txt, these functions to
 *	basically the same.  The map function does also build a
 *	scatterlist for the buffer (and unmap frees it ...)
 *
 * videobuf_dma_free()
 *	no comment ...
 *
 */

struct videobuf_dmabuf {
	u32                 magic;

	/* for userland buffer */
	int                 offset;
	size_t		    size;
	struct page         **pages;

	/* for kernel buffers */
	void                *vaddr;

	/* for overlay buffers (pci-pci dma) */
	dma_addr_t          bus_addr;

	/* common */
	struct scatterlist  *sglist;
	int                 sglen;
	int                 nr_pages;
	int                 direction;
};

struct videobuf_dma_sg_memory {
	u32                 magic;

	/* for mmap'ed buffers */
	struct videobuf_dmabuf  dma;
};

/*
 * Scatter-gather DMA buffer API.
 *
 * These functions provide a simple way to create a page list and a
 * scatter-gather list from a kernel, userspace of physical address and map the
 * memory for DMA operation.
 *
 * Despite the name, this is totally unrelated to videobuf, except that
 * videobuf-dma-sg uses the same API internally.
 */
void videobuf_dma_init(struct videobuf_dmabuf *dma);
int videobuf_dma_init_user(struct videobuf_dmabuf *dma, int direction,
			   unsigned long data, unsigned long size);
int videobuf_dma_init_kernel(struct videobuf_dmabuf *dma, int direction,
			     int nr_pages);
int videobuf_dma_init_overlay(struct videobuf_dmabuf *dma, int direction,
			      dma_addr_t addr, int nr_pages);
int videobuf_dma_free(struct videobuf_dmabuf *dma);

int videobuf_dma_map(struct device *dev, struct videobuf_dmabuf *dma);
int videobuf_dma_unmap(struct device *dev, struct videobuf_dmabuf *dma);
struct videobuf_dmabuf *videobuf_to_dma(struct videobuf_buffer *buf);

void *videobuf_sg_alloc(size_t size);

void videobuf_queue_sg_init(struct videobuf_queue *q,
			 const struct videobuf_queue_ops *ops,
			 struct device *dev,
			 spinlock_t *irqlock,
			 enum v4l2_buf_type type,
			 enum v4l2_field field,
			 unsigned int msize,
			 void *priv,
			 struct mutex *ext_lock);

#endif /* _VIDEOBUF_DMA_SG_H */

