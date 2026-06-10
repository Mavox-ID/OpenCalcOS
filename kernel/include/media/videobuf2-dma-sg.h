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
#ifndef _MEDIA_VIDEOBUF2_DMA_SG_H
#define _MEDIA_VIDEOBUF2_DMA_SG_H

#include <media/videobuf2-core.h>

struct vb2_dma_sg_desc {
	unsigned long		size;
	unsigned int		num_pages;
	struct scatterlist	*sglist;
};

static inline struct vb2_dma_sg_desc *vb2_dma_sg_plane_desc(
		struct vb2_buffer *vb, unsigned int plane_no)
{
	return (struct vb2_dma_sg_desc *)vb2_plane_cookie(vb, plane_no);
}

extern const struct vb2_mem_ops vb2_dma_sg_memops;

#endif
