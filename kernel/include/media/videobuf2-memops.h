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
#ifndef _MEDIA_VIDEOBUF2_MEMOPS_H
#define _MEDIA_VIDEOBUF2_MEMOPS_H

#include <media/videobuf2-core.h>

/**
 * vb2_vmarea_handler - common vma refcount tracking handler
 * @refcount:	pointer to refcount entry in the buffer
 * @put:	callback to function that decreases buffer refcount
 * @arg:	argument for @put callback
 */
struct vb2_vmarea_handler {
	atomic_t		*refcount;
	void			(*put)(void *arg);
	void			*arg;
};

extern const struct vm_operations_struct vb2_common_vm_ops;

int vb2_get_contig_userptr(unsigned long vaddr, unsigned long size,
			   struct vm_area_struct **res_vma, dma_addr_t *res_pa);

struct vm_area_struct *vb2_get_vma(struct vm_area_struct *vma);
void vb2_put_vma(struct vm_area_struct *vma);


#endif
