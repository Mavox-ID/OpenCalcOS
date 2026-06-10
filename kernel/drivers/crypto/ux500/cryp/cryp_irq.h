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
#ifndef _CRYP_IRQ_H_
#define _CRYP_IRQ_H_

#include "cryp.h"

enum cryp_irq_src_id {
	CRYP_IRQ_SRC_INPUT_FIFO = 0x1,
	CRYP_IRQ_SRC_OUTPUT_FIFO = 0x2,
	CRYP_IRQ_SRC_ALL = 0x3
};

/**
 * M0 Funtions
 */
void cryp_enable_irq_src(struct cryp_device_data *device_data, u32 irq_src);

void cryp_disable_irq_src(struct cryp_device_data *device_data, u32 irq_src);

bool cryp_pending_irq_src(struct cryp_device_data *device_data, u32 irq_src);

#endif				/* _CRYP_IRQ_H_ */
