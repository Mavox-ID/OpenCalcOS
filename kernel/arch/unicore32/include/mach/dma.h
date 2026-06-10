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
#ifndef __MACH_PUV3_DMA_H__
#define __MACH_PUV3_DMA_H__

/*
 * The PKUnity has six internal DMA channels.
 */
#define MAX_DMA_CHANNELS	6

typedef enum {
	DMA_PRIO_HIGH = 0,
	DMA_PRIO_MEDIUM = 1,
	DMA_PRIO_LOW = 2
} puv3_dma_prio;

/*
 * DMA registration
 */

extern int puv3_request_dma(char *name,
			 puv3_dma_prio prio,
			 void (*irq_handler)(int, void *),
			 void (*err_handler)(int, void *),
			 void *data);

extern void puv3_free_dma(int dma_ch);

static inline void puv3_stop_dma(int ch)
{
	writel(readl(DMAC_CONFIG(ch)) & ~DMAC_CONFIG_EN, DMAC_CONFIG(ch));
}

static inline void puv3_resume_dma(int ch)
{
	writel(readl(DMAC_CONFIG(ch)) | DMAC_CONFIG_EN, DMAC_CONFIG(ch));
}

#endif /* __MACH_PUV3_DMA_H__ */
