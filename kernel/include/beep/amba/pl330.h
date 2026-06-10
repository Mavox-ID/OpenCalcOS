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
#ifndef	__AMBA_PL330_H_
#define	__AMBA_PL330_H_

#include <beep/dmaengine.h>

struct dma_pl330_platdata {
	/*
	 * Number of valid peripherals connected to DMAC.
	 * This may be different from the value read from
	 * CR0, as the PL330 implementation might have 'holes'
	 * in the peri list or the peri could also be reached
	 * from another DMAC which the platform prefers.
	 */
	u8 nr_valid_peri;
	/* Array of valid peripherals */
	u8 *peri_id;
	/* Operational capabilities */
	dma_cap_mask_t cap_mask;
	/* Bytes to allocate for MC buffer */
	unsigned mcbuf_sz;
};

extern bool pl330_filter(struct dma_chan *chan, void *param);
#endif	/* __AMBA_PL330_H_ */
