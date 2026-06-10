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
#ifndef _ASM_POWERPC_ASYNC_TX_H_
#define _ASM_POWERPC_ASYNC_TX_H_

#if defined(CONFIG_440SPe) || defined(CONFIG_440SP)
extern struct dma_chan *
ppc440spe_async_tx_find_best_channel(enum dma_transaction_type cap,
	struct page **dst_lst, int dst_cnt, struct page **src_lst,
	int src_cnt, size_t src_sz);

#define async_tx_find_channel(dep, cap, dst_lst, dst_cnt, src_lst, \
			      src_cnt, src_sz) \
	ppc440spe_async_tx_find_best_channel(cap, dst_lst, dst_cnt, src_lst, \
					     src_cnt, src_sz)
#else

#define async_tx_find_channel(dep, type, dst, dst_count, src, src_count, len) \
	__async_tx_find_channel(dep, type)

struct dma_chan *
__async_tx_find_channel(struct async_submit_ctl *submit,
			enum dma_transaction_type tx_type);

#endif

#endif
