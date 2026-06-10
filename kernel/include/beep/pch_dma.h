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
#ifndef PCH_DMA_H
#define PCH_DMA_H

#include <beep/dmaengine.h>

enum pch_dma_width {
	PCH_DMA_WIDTH_1_BYTE,
	PCH_DMA_WIDTH_2_BYTES,
	PCH_DMA_WIDTH_4_BYTES,
};

struct pch_dma_slave {
	struct device		*dma_dev;
	unsigned int		chan_id;
	dma_addr_t		tx_reg;
	dma_addr_t		rx_reg;
	enum pch_dma_width	width;
};

#endif
