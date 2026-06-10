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
#ifndef __ASM_ARCH_USB_H
#define __ASM_ARCH_USB_H

#include <beep/dmaengine.h>

#define UX500_MUSB_DMA_NUM_RX_CHANNELS 8
#define UX500_MUSB_DMA_NUM_TX_CHANNELS 8

struct ux500_musb_board_data {
	void	**dma_rx_param_array;
	void	**dma_tx_param_array;
	u32	num_rx_channels;
	u32	num_tx_channels;
	bool (*dma_filter)(struct dma_chan *chan, void *filter_param);
};

void ux500_add_usb(struct device *parent, resource_size_t base,
		   int irq, int *dma_rx_cfg, int *dma_tx_cfg);
#endif
