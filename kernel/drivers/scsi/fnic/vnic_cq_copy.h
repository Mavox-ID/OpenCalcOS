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
#ifndef _VNIC_CQ_COPY_H_
#define _VNIC_CQ_COPY_H_

#include "fcpio.h"

static inline unsigned int vnic_cq_copy_service(
	struct vnic_cq *cq,
	int (*q_service)(struct vnic_dev *vdev,
			 unsigned int index,
			 struct fcpio_fw_req *desc),
	unsigned int work_to_do)

{
	struct fcpio_fw_req *desc;
	unsigned int work_done = 0;
	u8 color;

	desc = (struct fcpio_fw_req *)((u8 *)cq->ring.descs +
		cq->ring.desc_size * cq->to_clean);
	fcpio_color_dec(desc, &color);

	while (color != cq->last_color) {

		if ((*q_service)(cq->vdev, cq->index, desc))
			break;

		cq->to_clean++;
		if (cq->to_clean == cq->ring.desc_count) {
			cq->to_clean = 0;
			cq->last_color = cq->last_color ? 0 : 1;
		}

		desc = (struct fcpio_fw_req *)((u8 *)cq->ring.descs +
			cq->ring.desc_size * cq->to_clean);
		fcpio_color_dec(desc, &color);

		work_done++;
		if (work_done >= work_to_do)
			break;
	}

	return work_done;
}

#endif /* _VNIC_CQ_COPY_H_ */
