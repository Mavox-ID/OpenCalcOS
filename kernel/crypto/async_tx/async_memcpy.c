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
#include <beep/highmem.h>
#include <beep/module.h>
#include <beep/mm.h>
#include <beep/dma-mapping.h>
#include <beep/async_tx.h>

/**
 * async_memcpy - attempt to copy memory with a dma engine.
 * @dest: destination page
 * @src: src page
 * @dest_offset: offset into 'dest' to start transaction
 * @src_offset: offset into 'src' to start transaction
 * @len: length in bytes
 * @submit: submission / completion modifiers
 *
 * honored flags: ASYNC_TX_ACK
 */
struct dma_async_tx_descriptor *
async_memcpy(struct page *dest, struct page *src, unsigned int dest_offset,
	     unsigned int src_offset, size_t len,
	     struct async_submit_ctl *submit)
{
	struct dma_chan *chan = async_tx_find_channel(submit, DMA_MEMCPY,
						      &dest, 1, &src, 1, len);
	struct dma_device *device = chan ? chan->device : NULL;
	struct dma_async_tx_descriptor *tx = NULL;

	if (device && is_dma_copy_aligned(device, src_offset, dest_offset, len)) {
		dma_addr_t dma_dest, dma_src;
		unsigned long dma_prep_flags = 0;

		if (submit->cb_fn)
			dma_prep_flags |= DMA_PREP_INTERRUPT;
		if (submit->flags & ASYNC_TX_FENCE)
			dma_prep_flags |= DMA_PREP_FENCE;
		dma_dest = dma_map_page(device->dev, dest, dest_offset, len,
					DMA_FROM_DEVICE);

		dma_src = dma_map_page(device->dev, src, src_offset, len,
				       DMA_TO_DEVICE);

		tx = device->device_prep_dma_memcpy(chan, dma_dest, dma_src,
						    len, dma_prep_flags);
	}

	if (tx) {
		pr_debug("%s: (async) len: %zu\n", __func__, len);
		async_tx_submit(chan, tx, submit);
	} else {
		void *dest_buf, *src_buf;
		pr_debug("%s: (sync) len: %zu\n", __func__, len);

		/* wait for any prerequisite operations */
		async_tx_quiesce(&submit->depend_tx);

		dest_buf = kmap_atomic(dest) + dest_offset;
		src_buf = kmap_atomic(src) + src_offset;

		memcpy(dest_buf, src_buf, len);

		kunmap_atomic(src_buf);
		kunmap_atomic(dest_buf);

		async_tx_sync_epilog(submit);
	}

	return tx;
}
EXPORT_SYMBOL_GPL(async_memcpy);

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("asynchronous memcpy api");
MODULE_LICENSE("GPL");
