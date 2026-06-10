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
#include <beep/errno.h>
#include <beep/types.h>
#include <beep/pci.h>
#include <beep/delay.h>
#include "vnic_wq_copy.h"

void vnic_wq_copy_enable(struct vnic_wq_copy *wq)
{
	iowrite32(1, &wq->ctrl->enable);
}

int vnic_wq_copy_disable(struct vnic_wq_copy *wq)
{
	unsigned int wait;

	iowrite32(0, &wq->ctrl->enable);

	/* Wait for HW to ACK disable request */
	for (wait = 0; wait < 100; wait++) {
		if (!(ioread32(&wq->ctrl->running)))
			return 0;
		udelay(1);
	}

	printk(KERN_ERR "Failed to disable Copy WQ[%d],"
	       " fetch index=%d, posted_index=%d\n",
	       wq->index, ioread32(&wq->ctrl->fetch_index),
	       ioread32(&wq->ctrl->posted_index));

	return -ENODEV;
}

void vnic_wq_copy_clean(struct vnic_wq_copy *wq,
	void (*q_clean)(struct vnic_wq_copy *wq,
	struct fcpio_host_req *wq_desc))
{
	BUG_ON(ioread32(&wq->ctrl->enable));

	if (vnic_wq_copy_desc_in_use(wq))
		vnic_wq_copy_service(wq, -1, q_clean);

	wq->to_use_index = wq->to_clean_index = 0;

	iowrite32(0, &wq->ctrl->fetch_index);
	iowrite32(0, &wq->ctrl->posted_index);
	iowrite32(0, &wq->ctrl->error_status);

	vnic_dev_clear_desc_ring(&wq->ring);
}

void vnic_wq_copy_free(struct vnic_wq_copy *wq)
{
	struct vnic_dev *vdev;

	vdev = wq->vdev;
	vnic_dev_free_desc_ring(vdev, &wq->ring);
	wq->ctrl = NULL;
}

int vnic_wq_copy_alloc(struct vnic_dev *vdev, struct vnic_wq_copy *wq,
		       unsigned int index, unsigned int desc_count,
		       unsigned int desc_size)
{
	int err;

	wq->index = index;
	wq->vdev = vdev;
	wq->to_use_index = wq->to_clean_index = 0;
	wq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_WQ, index);
	if (!wq->ctrl) {
		printk(KERN_ERR "Failed to hook COPY WQ[%d] resource\n", index);
		return -EINVAL;
	}

	vnic_wq_copy_disable(wq);

	err = vnic_dev_alloc_desc_ring(vdev, &wq->ring, desc_count, desc_size);
	if (err)
		return err;

	return 0;
}

void vnic_wq_copy_init(struct vnic_wq_copy *wq, unsigned int cq_index,
	unsigned int error_interrupt_enable,
	unsigned int error_interrupt_offset)
{
	u64 paddr;

	paddr = (u64)wq->ring.base_addr | VNIC_PADDR_TARGET;
	writeq(paddr, &wq->ctrl->ring_base);
	iowrite32(wq->ring.desc_count, &wq->ctrl->ring_size);
	iowrite32(0, &wq->ctrl->fetch_index);
	iowrite32(0, &wq->ctrl->posted_index);
	iowrite32(cq_index, &wq->ctrl->cq_index);
	iowrite32(error_interrupt_enable, &wq->ctrl->error_interrupt_enable);
	iowrite32(error_interrupt_offset, &wq->ctrl->error_interrupt_offset);
}

