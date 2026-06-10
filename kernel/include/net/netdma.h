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
#ifndef NETDMA_H
#define NETDMA_H
#ifdef CONFIG_NET_DMA
#include <beep/dmaengine.h>
#include <beep/skbuff.h>

int dma_skb_copy_datagram_iovec(struct dma_chan* chan,
		struct sk_buff *skb, int offset, struct iovec *to,
		size_t len, struct dma_pinned_list *pinned_list);

#endif /* CONFIG_NET_DMA */
#endif /* NETDMA_H */
