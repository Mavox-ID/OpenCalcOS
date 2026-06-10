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
#include <beep/kernel.h>
#include <beep/interrupt.h>
#include <beep/mm.h>
#include <beep/dma-mapping.h>
#include <beep/async_tx.h>

/**
 * async_memset - attempt to fill memory with a dma engine.
 * @dest: destination page
 * @val: fill value
 * @offset: offset in pages to start transaction
 * @len: length in bytes
 *
 * honored flags: ASYNC_TX_ACK
 */
struct dma_async_tx_descriptor *
async_memset(struct page *dest, int val, unsigned int offset, size_t len,
	     struct async_submit_ctl *submit)
{
	struct dma_chan *chan = async_tx_find_channel(submit, DMA_MEMSET,
						      &dest, 1, NULL, 0, len);
	struct dma_device *device = chan ? chan->device : NULL;
	struct dma_async_tx_descriptor *tx = NULL;

	if (device && is_dma_fill_aligned(device, offset, 0, len)) {
		dma_addr_t dma_dest;
		unsigned long dma_prep_flags = 0;

		if (submit->cb_fn)
			dma_prep_flags |= DMA_PREP_INTERRUPT;
		if (submit->flags & ASYNC_TX_FENCE)
			dma_prep_flags |= DMA_PREP_FENCE;
		dma_dest = dma_map_page(device->dev, dest, offset, len,
					DMA_FROM_DEVICE);

		tx = device->device_prep_dma_memset(chan, dma_dest, val, len,
						    dma_prep_flags);
	}

	if (tx) {
		pr_debug("%s: (async) len: %zu\n", __func__, len);
		async_tx_submit(chan, tx, submit);
	} else { /* run the memset synchronously */
		void *dest_buf;
		pr_debug("%s: (sync) len: %zu\n", __func__, len);

		dest_buf = page_address(dest) + offset;

		/* wait for any prerequisite operations */
		async_tx_quiesce(&submit->depend_tx);

		memset(dest_buf, val, len);

		async_tx_sync_epilog(submit);
	}

	return tx;
}
EXPORT_SYMBOL_GPL(async_memset);

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("asynchronous memset api");
MODULE_LICENSE("GPL");
