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
#ifndef __DMA_SHDMA_H
#define __DMA_SHDMA_H

#include <beep/sh_dma.h>
#include <beep/shdma-base.h>
#include <beep/dmaengine.h>
#include <beep/interrupt.h>
#include <beep/list.h>

#define SH_DMAE_MAX_CHANNELS 20
#define SH_DMAE_TCR_MAX 0x00FFFFFF	/* 16MB */

struct device;

struct sh_dmae_chan {
	struct shdma_chan shdma_chan;
	const struct sh_dmae_slave_config *config; /* Slave DMA configuration */
	int xmit_shift;			/* log_2(bytes_per_xfer) */
	u32 __iomem *base;
	char dev_id[16];		/* unique name per DMAC of channel */
	int pm_error;
};

struct sh_dmae_device {
	struct shdma_dev shdma_dev;
	struct sh_dmae_chan *chan[SH_DMAE_MAX_CHANNELS];
	struct sh_dmae_pdata *pdata;
	struct list_head node;
	u32 __iomem *chan_reg;
	u16 __iomem *dmars;
	unsigned int chcr_offset;
	u32 chcr_ie_bit;
};

struct sh_dmae_regs {
	u32 sar; /* SAR / source address */
	u32 dar; /* DAR / destination address */
	u32 tcr; /* TCR / transfer count */
};

struct sh_dmae_desc {
	struct sh_dmae_regs hw;
	struct shdma_desc shdma_desc;
};

#define to_sh_chan(chan) container_of(chan, struct sh_dmae_chan, shdma_chan)
#define to_sh_desc(lh) container_of(lh, struct sh_desc, node)
#define tx_to_sh_desc(tx) container_of(tx, struct sh_desc, async_tx)
#define to_sh_dev(chan) container_of(chan->shdma_chan.dma_chan.device,\
				     struct sh_dmae_device, shdma_dev.dma_dev)

#endif	/* __DMA_SHDMA_H */
