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
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/types.h>
#include <beep/pci.h>
#include <beep/delay.h>
#include <beep/slab.h>

#include "vnic_dev.h"
#include "vnic_wq.h"

static int vnic_wq_alloc_bufs(struct vnic_wq *wq)
{
	struct vnic_wq_buf *buf;
	struct vnic_dev *vdev;
	unsigned int i, j, count = wq->ring.desc_count;
	unsigned int blks = VNIC_WQ_BUF_BLKS_NEEDED(count);

	vdev = wq->vdev;

	for (i = 0; i < blks; i++) {
		wq->bufs[i] = kzalloc(VNIC_WQ_BUF_BLK_SZ(count), GFP_ATOMIC);
		if (!wq->bufs[i])
			return -ENOMEM;
	}

	for (i = 0; i < blks; i++) {
		buf = wq->bufs[i];
		for (j = 0; j < VNIC_WQ_BUF_BLK_ENTRIES(count); j++) {
			buf->index = i * VNIC_WQ_BUF_BLK_ENTRIES(count) + j;
			buf->desc = (u8 *)wq->ring.descs +
				wq->ring.desc_size * buf->index;
			if (buf->index + 1 == count) {
				buf->next = wq->bufs[0];
				break;
			} else if (j + 1 == VNIC_WQ_BUF_BLK_ENTRIES(count)) {
				buf->next = wq->bufs[i + 1];
			} else {
				buf->next = buf + 1;
				buf++;
			}
		}
	}

	wq->to_use = wq->to_clean = wq->bufs[0];

	return 0;
}

void vnic_wq_free(struct vnic_wq *wq)
{
	struct vnic_dev *vdev;
	unsigned int i;

	vdev = wq->vdev;

	vnic_dev_free_desc_ring(vdev, &wq->ring);

	for (i = 0; i < VNIC_WQ_BUF_BLKS_MAX; i++) {
		if (wq->bufs[i]) {
			kfree(wq->bufs[i]);
			wq->bufs[i] = NULL;
		}
	}

	wq->ctrl = NULL;
}

int vnic_wq_alloc(struct vnic_dev *vdev, struct vnic_wq *wq, unsigned int index,
	unsigned int desc_count, unsigned int desc_size)
{
	int err;

	wq->index = index;
	wq->vdev = vdev;

	wq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_WQ, index);
	if (!wq->ctrl) {
		pr_err("Failed to hook WQ[%d] resource\n", index);
		return -EINVAL;
	}

	vnic_wq_disable(wq);

	err = vnic_dev_alloc_desc_ring(vdev, &wq->ring, desc_count, desc_size);
	if (err)
		return err;

	err = vnic_wq_alloc_bufs(wq);
	if (err) {
		vnic_wq_free(wq);
		return err;
	}

	return 0;
}

static void vnic_wq_init_start(struct vnic_wq *wq, unsigned int cq_index,
	unsigned int fetch_index, unsigned int posted_index,
	unsigned int error_interrupt_enable,
	unsigned int error_interrupt_offset)
{
	u64 paddr;
	unsigned int count = wq->ring.desc_count;

	paddr = (u64)wq->ring.base_addr | VNIC_PADDR_TARGET;
	writeq(paddr, &wq->ctrl->ring_base);
	iowrite32(count, &wq->ctrl->ring_size);
	iowrite32(fetch_index, &wq->ctrl->fetch_index);
	iowrite32(posted_index, &wq->ctrl->posted_index);
	iowrite32(cq_index, &wq->ctrl->cq_index);
	iowrite32(error_interrupt_enable, &wq->ctrl->error_interrupt_enable);
	iowrite32(error_interrupt_offset, &wq->ctrl->error_interrupt_offset);
	iowrite32(0, &wq->ctrl->error_status);

	wq->to_use = wq->to_clean =
		&wq->bufs[fetch_index / VNIC_WQ_BUF_BLK_ENTRIES(count)]
			[fetch_index % VNIC_WQ_BUF_BLK_ENTRIES(count)];
}

void vnic_wq_init(struct vnic_wq *wq, unsigned int cq_index,
	unsigned int error_interrupt_enable,
	unsigned int error_interrupt_offset)
{
	vnic_wq_init_start(wq, cq_index, 0, 0,
		error_interrupt_enable,
		error_interrupt_offset);
}

unsigned int vnic_wq_error_status(struct vnic_wq *wq)
{
	return ioread32(&wq->ctrl->error_status);
}

void vnic_wq_enable(struct vnic_wq *wq)
{
	iowrite32(1, &wq->ctrl->enable);
}

int vnic_wq_disable(struct vnic_wq *wq)
{
	unsigned int wait;

	iowrite32(0, &wq->ctrl->enable);

	/* Wait for HW to ACK disable request */
	for (wait = 0; wait < 1000; wait++) {
		if (!(ioread32(&wq->ctrl->running)))
			return 0;
		udelay(10);
	}

	pr_err("Failed to disable WQ[%d]\n", wq->index);

	return -ETIMEDOUT;
}

void vnic_wq_clean(struct vnic_wq *wq,
	void (*buf_clean)(struct vnic_wq *wq, struct vnic_wq_buf *buf))
{
	struct vnic_wq_buf *buf;

	buf = wq->to_clean;

	while (vnic_wq_desc_used(wq) > 0) {

		(*buf_clean)(wq, buf);

		buf = wq->to_clean = buf->next;
		wq->ring.desc_avail++;
	}

	wq->to_use = wq->to_clean = wq->bufs[0];

	iowrite32(0, &wq->ctrl->fetch_index);
	iowrite32(0, &wq->ctrl->posted_index);
	iowrite32(0, &wq->ctrl->error_status);

	vnic_dev_clear_desc_ring(&wq->ring);
}
