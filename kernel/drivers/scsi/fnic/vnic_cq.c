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
#include "vnic_dev.h"
#include "vnic_cq.h"

void vnic_cq_free(struct vnic_cq *cq)
{
	vnic_dev_free_desc_ring(cq->vdev, &cq->ring);

	cq->ctrl = NULL;
}

int vnic_cq_alloc(struct vnic_dev *vdev, struct vnic_cq *cq, unsigned int index,
	unsigned int desc_count, unsigned int desc_size)
{
	int err;

	cq->index = index;
	cq->vdev = vdev;

	cq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_CQ, index);
	if (!cq->ctrl) {
		printk(KERN_ERR "Failed to hook CQ[%d] resource\n", index);
		return -EINVAL;
	}

	err = vnic_dev_alloc_desc_ring(vdev, &cq->ring, desc_count, desc_size);
	if (err)
		return err;

	return 0;
}

void vnic_cq_init(struct vnic_cq *cq, unsigned int flow_control_enable,
	unsigned int color_enable, unsigned int cq_head, unsigned int cq_tail,
	unsigned int cq_tail_color, unsigned int interrupt_enable,
	unsigned int cq_entry_enable, unsigned int cq_message_enable,
	unsigned int interrupt_offset, u64 cq_message_addr)
{
	u64 paddr;

	paddr = (u64)cq->ring.base_addr | VNIC_PADDR_TARGET;
	writeq(paddr, &cq->ctrl->ring_base);
	iowrite32(cq->ring.desc_count, &cq->ctrl->ring_size);
	iowrite32(flow_control_enable, &cq->ctrl->flow_control_enable);
	iowrite32(color_enable, &cq->ctrl->color_enable);
	iowrite32(cq_head, &cq->ctrl->cq_head);
	iowrite32(cq_tail, &cq->ctrl->cq_tail);
	iowrite32(cq_tail_color, &cq->ctrl->cq_tail_color);
	iowrite32(interrupt_enable, &cq->ctrl->interrupt_enable);
	iowrite32(cq_entry_enable, &cq->ctrl->cq_entry_enable);
	iowrite32(cq_message_enable, &cq->ctrl->cq_message_enable);
	iowrite32(interrupt_offset, &cq->ctrl->interrupt_offset);
	writeq(cq_message_addr, &cq->ctrl->cq_message_addr);
}

void vnic_cq_clean(struct vnic_cq *cq)
{
	cq->to_clean = 0;
	cq->last_color = 0;

	iowrite32(0, &cq->ctrl->cq_head);
	iowrite32(0, &cq->ctrl->cq_tail);
	iowrite32(1, &cq->ctrl->cq_tail_color);

	vnic_dev_clear_desc_ring(&cq->ring);
}
