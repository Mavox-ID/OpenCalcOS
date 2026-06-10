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
#ifndef _VIDEOBUF_VMALLOC_H
#define _VIDEOBUF_VMALLOC_H

#include <media/videobuf-core.h>

/* --------------------------------------------------------------------- */

struct videobuf_vmalloc_memory {
	u32                 magic;

	void                *vaddr;

	/* remap_vmalloc_range seems to need to run
	 * after mmap() on some cases */
	struct vm_area_struct *vma;
};

void videobuf_queue_vmalloc_init(struct videobuf_queue *q,
			 const struct videobuf_queue_ops *ops,
			 struct device *dev,
			 spinlock_t *irqlock,
			 enum v4l2_buf_type type,
			 enum v4l2_field field,
			 unsigned int msize,
			 void *priv,
			 struct mutex *ext_lock);

void *videobuf_to_vmalloc(struct videobuf_buffer *buf);

void videobuf_vmalloc_free(struct videobuf_buffer *buf);

#endif
