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

#include "vnic_dev.h"
#include "vnic_intr.h"

void vnic_intr_free(struct vnic_intr *intr)
{
	intr->ctrl = NULL;
}

int vnic_intr_alloc(struct vnic_dev *vdev, struct vnic_intr *intr,
	unsigned int index)
{
	intr->index = index;
	intr->vdev = vdev;

	intr->ctrl = vnic_dev_get_res(vdev, RES_TYPE_INTR_CTRL, index);
	if (!intr->ctrl) {
		pr_err("Failed to hook INTR[%d].ctrl resource\n", index);
		return -EINVAL;
	}

	return 0;
}

void vnic_intr_init(struct vnic_intr *intr, u32 coalescing_timer,
	unsigned int coalescing_type, unsigned int mask_on_assertion)
{
	vnic_intr_coalescing_timer_set(intr, coalescing_timer);
	iowrite32(coalescing_type, &intr->ctrl->coalescing_type);
	iowrite32(mask_on_assertion, &intr->ctrl->mask_on_assertion);
	iowrite32(0, &intr->ctrl->int_credits);
}

void vnic_intr_coalescing_timer_set(struct vnic_intr *intr,
	u32 coalescing_timer)
{
	iowrite32(vnic_dev_intr_coal_timer_usec_to_hw(intr->vdev,
		coalescing_timer), &intr->ctrl->coalescing_timer);
}

void vnic_intr_clean(struct vnic_intr *intr)
{
	iowrite32(0, &intr->ctrl->int_credits);
}
