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
#include <plat/dma-core.h>

extern struct bus_type dma_subsys;
extern struct s3c2410_dma_chan s3c2410_chans[S3C_DMA_CHANNELS];

#define DMA_CH_VALID		(1<<31)
#define DMA_CH_NEVER		(1<<30)

/* struct s3c24xx_dma_map
 *
 * this holds the mapping information for the channel selected
 * to be connected to the specified device
*/

struct s3c24xx_dma_map {
	const char		*name;

	unsigned long		 channels[S3C_DMA_CHANNELS];
	unsigned long		 channels_rx[S3C_DMA_CHANNELS];
};

struct s3c24xx_dma_selection {
	struct s3c24xx_dma_map	*map;
	unsigned long		 map_size;
	unsigned long		 dcon_mask;

	void	(*select)(struct s3c2410_dma_chan *chan,
			  struct s3c24xx_dma_map *map);

	void	(*direction)(struct s3c2410_dma_chan *chan,
			     struct s3c24xx_dma_map *map,
			     enum dma_data_direction dir);
};

extern int s3c24xx_dma_init_map(struct s3c24xx_dma_selection *sel);

/* struct s3c24xx_dma_order_ch
 *
 * channel map for one of the `enum dma_ch` dma channels. the list
 * entry contains a set of low-level channel numbers, orred with
 * DMA_CH_VALID, which are checked in the order in the array.
*/

struct s3c24xx_dma_order_ch {
	unsigned int	list[S3C_DMA_CHANNELS];	/* list of channels */
	unsigned int	flags;				/* flags */
};

/* struct s3c24xx_dma_order
 *
 * information provided by either the core or the board to give the
 * dma system a hint on how to allocate channels
*/

struct s3c24xx_dma_order {
	struct s3c24xx_dma_order_ch	channels[DMACH_MAX];
};

extern int s3c24xx_dma_order_set(struct s3c24xx_dma_order *map);

/* DMA init code, called from the cpu support code */

extern int s3c2410_dma_init(void);

extern int s3c24xx_dma_init(unsigned int channels, unsigned int irq,
			    unsigned int stride);
