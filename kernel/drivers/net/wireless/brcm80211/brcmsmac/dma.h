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
#ifndef	_BRCM_DMA_H_
#define	_BRCM_DMA_H_

#include <beep/delay.h>
#include <beep/skbuff.h>
#include "types.h"		/* forward structure declarations */

/* map/unmap direction */
#define	DMA_TX	1		/* TX direction for DMA */
#define	DMA_RX	2		/* RX direction for DMA */

/* DMA structure:
 *  support two DMA engines: 32 bits address or 64 bit addressing
 *  basic DMA register set is per channel(transmit or receive)
 *  a pair of channels is defined for convenience
 */

/* 32 bits addressing */

struct dma32diag {	/* diag access */
	u32 fifoaddr;	/* diag address */
	u32 fifodatalow;	/* low 32bits of data */
	u32 fifodatahigh;	/* high 32bits of data */
	u32 pad;		/* reserved */
};

/* 64 bits addressing */

/* dma registers per channel(xmt or rcv) */
struct dma64regs {
	u32 control;	/* enable, et al */
	u32 ptr;	/* last descriptor posted to chip */
	u32 addrlow;	/* desc ring base address low 32-bits (8K aligned) */
	u32 addrhigh;	/* desc ring base address bits 63:32 (8K aligned) */
	u32 status0;	/* current descriptor, xmt state */
	u32 status1;	/* active descriptor, xmt error */
};

/* range param for dma_getnexttxp() and dma_txreclaim */
enum txd_range {
	DMA_RANGE_ALL = 1,
	DMA_RANGE_TRANSMITTED,
	DMA_RANGE_TRANSFERED
};

/*
 * Exported data structure (read-only)
 */
/* export structure */
struct dma_pub {
	uint txavail;		/* # free tx descriptors */
	uint dmactrlflags;	/* dma control flags */

	/* rx error counters */
	uint rxgiants;		/* rx giant frames */
	uint rxnobuf;		/* rx out of dma descriptors */
	/* tx error counters */
	uint txnobuf;		/* tx out of dma descriptors */
};

extern struct dma_pub *dma_attach(char *name, struct brcms_c_info *wlc,
				  uint txregbase, uint rxregbase,
				  uint ntxd, uint nrxd,
				  uint rxbufsize, int rxextheadroom,
				  uint nrxpost, uint rxoffset);

void dma_rxinit(struct dma_pub *pub);
int dma_rx(struct dma_pub *pub, struct sk_buff_head *skb_list);
bool dma_rxfill(struct dma_pub *pub);
bool dma_rxreset(struct dma_pub *pub);
bool dma_txreset(struct dma_pub *pub);
void dma_txinit(struct dma_pub *pub);
int dma_txfast(struct brcms_c_info *wlc, struct dma_pub *pub,
	       struct sk_buff *p0);
void dma_txflush(struct dma_pub *pub);
int dma_txpending(struct dma_pub *pub);
void dma_kick_tx(struct dma_pub *pub);
void dma_txsuspend(struct dma_pub *pub);
bool dma_txsuspended(struct dma_pub *pub);
void dma_txresume(struct dma_pub *pub);
void dma_txreclaim(struct dma_pub *pub, enum txd_range range);
void dma_rxreclaim(struct dma_pub *pub);
void dma_detach(struct dma_pub *pub);
unsigned long dma_getvar(struct dma_pub *pub, const char *name);
struct sk_buff *dma_getnexttxp(struct dma_pub *pub, enum txd_range range);
void dma_counterreset(struct dma_pub *pub);

void dma_walk_packets(struct dma_pub *dmah, void (*callback_fnc)
		      (void *pkt, void *arg_a), void *arg_a);

/*
 * DMA(Bug) on bcm47xx chips seems to declare that the packet is ready, but
 * the packet length is not updated yet (by DMA) on the expected time.
 * Workaround is to hold processor till DMA updates the length, and stay off
 * the bus to allow DMA update the length in buffer
 */
static inline void dma_spin_for_len(uint len, struct sk_buff *head)
{
#if defined(CONFIG_BCM47XX)
	if (!len) {
		while (!(len = *(u16 *) KSEG1ADDR(head->data)))
			udelay(1);

		*(u16 *) (head->data) = cpu_to_le16((u16) len);
	}
#endif				/* defined(CONFIG_BCM47XX) */
}

#endif				/* _BRCM_DMA_H_ */
