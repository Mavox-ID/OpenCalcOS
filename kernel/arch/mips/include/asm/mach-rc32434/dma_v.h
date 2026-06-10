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
#ifndef _ASM_RC32434_DMA_V_H_
#define _ASM_RC32434_DMA_V_H_

#include  <asm/mach-rc32434/dma.h>
#include  <asm/mach-rc32434/rc32434.h>

#define DMA_CHAN_OFFSET		0x14
#define IS_DMA_USED(X)		(((X) & \
				(DMA_DESC_FINI | DMA_DESC_DONE | DMA_DESC_TERM)) \
				!= 0)
#define DMA_COUNT(count)	((count) & DMA_DESC_COUNT_MSK)

#define DMA_HALT_TIMEOUT	500

static inline int rc32434_halt_dma(struct dma_reg *ch)
{
	int timeout = 1;
	if (__raw_readl(&ch->dmac) & DMA_CHAN_RUN_BIT) {
		__raw_writel(0, &ch->dmac);
		for (timeout = DMA_HALT_TIMEOUT; timeout > 0; timeout--) {
			if (__raw_readl(&ch->dmas) & DMA_STAT_HALT) {
				__raw_writel(0, &ch->dmas);
				break;
			}
		}
	}

	return timeout ? 0 : 1;
}

static inline void rc32434_start_dma(struct dma_reg *ch, u32 dma_addr)
{
	__raw_writel(0, &ch->dmandptr);
	__raw_writel(dma_addr, &ch->dmadptr);
}

static inline void rc32434_chain_dma(struct dma_reg *ch, u32 dma_addr)
{
	__raw_writel(dma_addr, &ch->dmandptr);
}

#endif  /* _ASM_RC32434_DMA_V_H_ */
