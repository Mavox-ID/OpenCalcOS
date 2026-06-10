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
#ifndef _VIDEOBUF_DMA_CONTIG_H
#define _VIDEOBUF_DMA_CONTIG_H

#include <beep/dma-mapping.h>
#include <media/videobuf-core.h>

void videobuf_queue_dma_contig_init(struct videobuf_queue *q,
				    const struct videobuf_queue_ops *ops,
				    struct device *dev,
				    spinlock_t *irqlock,
				    enum v4l2_buf_type type,
				    enum v4l2_field field,
				    unsigned int msize,
				    void *priv,
				    struct mutex *ext_lock);

void videobuf_queue_dma_contig_init_cached(struct videobuf_queue *q,
					   const struct videobuf_queue_ops *ops,
					   struct device *dev,
					   spinlock_t *irqlock,
					   enum v4l2_buf_type type,
					   enum v4l2_field field,
					   unsigned int msize,
					   void *priv,
					   struct mutex *ext_lock);

dma_addr_t videobuf_to_dma_contig(struct videobuf_buffer *buf);
void videobuf_dma_contig_free(struct videobuf_queue *q,
			      struct videobuf_buffer *buf);

#endif /* _VIDEOBUF_DMA_CONTIG_H */
