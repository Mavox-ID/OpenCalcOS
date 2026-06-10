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
#include "stmmac.h"

unsigned int stmmac_jumbo_frm(void *p, struct sk_buff *skb, int csum)
{
	struct stmmac_priv *priv = (struct stmmac_priv *) p;
	unsigned int txsize = priv->dma_tx_size;
	unsigned int entry = priv->cur_tx % txsize;
	struct dma_desc *desc = priv->dma_tx + entry;
	unsigned int nopaged_len = skb_headlen(skb);
	unsigned int bmax;
	unsigned int i = 1, len;

	if (priv->plat->enh_desc)
		bmax = BUF_SIZE_8KiB;
	else
		bmax = BUF_SIZE_2KiB;

	len = nopaged_len - bmax;

	desc->des2 = dma_map_single(priv->device, skb->data,
				    bmax, DMA_TO_DEVICE);
	priv->hw->desc->prepare_tx_desc(desc, 1, bmax, csum);

	while (len != 0) {
		entry = (++priv->cur_tx) % txsize;
		desc = priv->dma_tx + entry;

		if (len > bmax) {
			desc->des2 = dma_map_single(priv->device,
						    (skb->data + bmax * i),
						    bmax, DMA_TO_DEVICE);
			priv->hw->desc->prepare_tx_desc(desc, 0, bmax,
							csum);
			priv->hw->desc->set_tx_owner(desc);
			priv->tx_skbuff[entry] = NULL;
			len -= bmax;
			i++;
		} else {
			desc->des2 = dma_map_single(priv->device,
						    (skb->data + bmax * i), len,
						    DMA_TO_DEVICE);
			priv->hw->desc->prepare_tx_desc(desc, 0, len,
							csum);
			priv->hw->desc->set_tx_owner(desc);
			priv->tx_skbuff[entry] = NULL;
			len = 0;
		}
	}
	return entry;
}

static unsigned int stmmac_is_jumbo_frm(int len, int enh_desc)
{
	unsigned int ret = 0;

	if ((enh_desc && (len > BUF_SIZE_8KiB)) ||
	    (!enh_desc && (len > BUF_SIZE_2KiB))) {
		ret = 1;
	}

	return ret;
}

static void stmmac_refill_desc3(int bfsize, struct dma_desc *p)
{
}

static void stmmac_init_desc3(int des3_as_data_buf, struct dma_desc *p)
{
}

static void stmmac_clean_desc3(struct dma_desc *p)
{
}

static void stmmac_init_dma_chain(struct dma_desc *des, dma_addr_t phy_addr,
				  unsigned int size)
{
	/*
	 * In chained mode the des3 points to the next element in the ring.
	 * The latest element has to point to the head.
	 */
	int i;
	struct dma_desc *p = des;
	dma_addr_t dma_phy = phy_addr;

	for (i = 0; i < (size - 1); i++) {
		dma_phy += sizeof(struct dma_desc);
		p->des3 = (unsigned int)dma_phy;
		p++;
	}
	p->des3 = (unsigned int)phy_addr;
}

static int stmmac_set_16kib_bfsize(int mtu)
{
	/* Not supported */
	return 0;
}

const struct stmmac_ring_mode_ops ring_mode_ops = {
	.is_jumbo_frm = stmmac_is_jumbo_frm,
	.jumbo_frm = stmmac_jumbo_frm,
	.refill_desc3 = stmmac_refill_desc3,
	.init_desc3 = stmmac_init_desc3,
	.init_dma_chain = stmmac_init_dma_chain,
	.clean_desc3 = stmmac_clean_desc3,
	.set_16kib_bfsize = stmmac_set_16kib_bfsize,
};
