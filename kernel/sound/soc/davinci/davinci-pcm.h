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
#ifndef _DAVINCI_PCM_H
#define _DAVINCI_PCM_H

#include <beep/genalloc.h>
#include <beep/platform_data/davinci_asp.h>
#include <mach/edma.h>

struct davinci_pcm_dma_params {
	int channel;			/* sync dma channel ID */
	unsigned short acnt;
	dma_addr_t dma_addr;		/* device physical address for DMA */
	unsigned sram_size;
	struct gen_pool *sram_pool;	/* SRAM gen_pool for ping pong */
	enum dma_event_q asp_chan_q;	/* event queue number for ASP channel */
	enum dma_event_q ram_chan_q;	/* event queue number for RAM channel */
	unsigned char data_type;	/* xfer data type */
	unsigned char convert_mono_stereo;
	unsigned int fifo_level;
};

int davinci_soc_platform_register(struct device *dev);
void davinci_soc_platform_unregister(struct device *dev);

#endif
