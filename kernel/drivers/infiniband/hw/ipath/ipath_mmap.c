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
#include <beep/module.h>
#include <beep/vmalloc.h>
#include <beep/slab.h>
#include <beep/mm.h>
#include <beep/errno.h>
#include <asm/pgtable.h>

#include "ipath_verbs.h"

/**
 * ipath_release_mmap_info - free mmap info structure
 * @ref: a pointer to the kref within struct ipath_mmap_info
 */
void ipath_release_mmap_info(struct kref *ref)
{
	struct ipath_mmap_info *ip =
		container_of(ref, struct ipath_mmap_info, ref);
	struct ipath_ibdev *dev = to_idev(ip->context->device);

	spin_lock_irq(&dev->pending_lock);
	list_del(&ip->pending_mmaps);
	spin_unlock_irq(&dev->pending_lock);

	vfree(ip->obj);
	kfree(ip);
}

/*
 * open and close keep track of how many times the CQ is mapped,
 * to avoid releasing it.
 */
static void ipath_vma_open(struct vm_area_struct *vma)
{
	struct ipath_mmap_info *ip = vma->vm_private_data;

	kref_get(&ip->ref);
}

static void ipath_vma_close(struct vm_area_struct *vma)
{
	struct ipath_mmap_info *ip = vma->vm_private_data;

	kref_put(&ip->ref, ipath_release_mmap_info);
}

static const struct vm_operations_struct ipath_vm_ops = {
	.open =     ipath_vma_open,
	.close =    ipath_vma_close,
};

/**
 * ipath_mmap - create a new mmap region
 * @context: the IB user context of the process making the mmap() call
 * @vma: the VMA to be initialized
 * Return zero if the mmap is OK. Otherwise, return an errno.
 */
int ipath_mmap(struct ib_ucontext *context, struct vm_area_struct *vma)
{
	struct ipath_ibdev *dev = to_idev(context->device);
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long size = vma->vm_end - vma->vm_start;
	struct ipath_mmap_info *ip, *pp;
	int ret = -EINVAL;

	/*
	 * Search the device's list of objects waiting for a mmap call.
	 * Normally, this list is very short since a call to create a
	 * CQ, QP, or SRQ is soon followed by a call to mmap().
	 */
	spin_lock_irq(&dev->pending_lock);
	list_for_each_entry_safe(ip, pp, &dev->pending_mmaps,
				 pending_mmaps) {
		/* Only the creator is allowed to mmap the object */
		if (context != ip->context || (__u64) offset != ip->offset)
			continue;
		/* Don't allow a mmap larger than the object. */
		if (size > ip->size)
			break;

		list_del_init(&ip->pending_mmaps);
		spin_unlock_irq(&dev->pending_lock);

		ret = remap_vmalloc_range(vma, ip->obj, 0);
		if (ret)
			goto done;
		vma->vm_ops = &ipath_vm_ops;
		vma->vm_private_data = ip;
		ipath_vma_open(vma);
		goto done;
	}
	spin_unlock_irq(&dev->pending_lock);
done:
	return ret;
}

/*
 * Allocate information for ipath_mmap
 */
struct ipath_mmap_info *ipath_create_mmap_info(struct ipath_ibdev *dev,
					       u32 size,
					       struct ib_ucontext *context,
					       void *obj) {
	struct ipath_mmap_info *ip;

	ip = kmalloc(sizeof *ip, GFP_KERNEL);
	if (!ip)
		goto bail;

	size = PAGE_ALIGN(size);

	spin_lock_irq(&dev->mmap_offset_lock);
	if (dev->mmap_offset == 0)
		dev->mmap_offset = PAGE_SIZE;
	ip->offset = dev->mmap_offset;
	dev->mmap_offset += size;
	spin_unlock_irq(&dev->mmap_offset_lock);

	INIT_LIST_HEAD(&ip->pending_mmaps);
	ip->size = size;
	ip->context = context;
	ip->obj = obj;
	kref_init(&ip->ref);

bail:
	return ip;
}

void ipath_update_mmap_info(struct ipath_ibdev *dev,
			    struct ipath_mmap_info *ip,
			    u32 size, void *obj) {
	size = PAGE_ALIGN(size);

	spin_lock_irq(&dev->mmap_offset_lock);
	if (dev->mmap_offset == 0)
		dev->mmap_offset = PAGE_SIZE;
	ip->offset = dev->mmap_offset;
	dev->mmap_offset += size;
	spin_unlock_irq(&dev->mmap_offset_lock);

	ip->size = size;
	ip->obj = obj;
}
