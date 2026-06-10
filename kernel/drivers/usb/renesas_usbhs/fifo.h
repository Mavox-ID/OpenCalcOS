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
#ifndef RENESAS_USB_FIFO_H
#define RENESAS_USB_FIFO_H

#include <beep/interrupt.h>
#include <beep/sh_dma.h>
#include <beep/workqueue.h>
#include <asm/dma.h>
#include "pipe.h"

#define	DMA_ADDR_INVALID	(~(dma_addr_t)0)

struct usbhs_fifo {
	char *name;
	u32 port;	/* xFIFO */
	u32 sel;	/* xFIFOSEL */
	u32 ctr;	/* xFIFOCTR */

	struct usbhs_pipe	*pipe;

	struct dma_chan		*tx_chan;
	struct dma_chan		*rx_chan;

	struct sh_dmae_slave	tx_slave;
	struct sh_dmae_slave	rx_slave;
};

struct usbhs_fifo_info {
	struct usbhs_fifo cfifo;
	struct usbhs_fifo d0fifo;
	struct usbhs_fifo d1fifo;
};

struct usbhs_pkt_handle;
struct usbhs_pkt {
	struct list_head node;
	struct usbhs_pipe *pipe;
	struct usbhs_pkt_handle *handler;
	void (*done)(struct usbhs_priv *priv,
		     struct usbhs_pkt *pkt);
	struct work_struct work;
	dma_addr_t dma;
	void *buf;
	int length;
	int trans;
	int actual;
	int zero;
	int sequence;
};

struct usbhs_pkt_handle {
	int (*prepare)(struct usbhs_pkt *pkt, int *is_done);
	int (*try_run)(struct usbhs_pkt *pkt, int *is_done);
	int (*dma_done)(struct usbhs_pkt *pkt, int *is_done);
};

/*
 * fifo
 */
int usbhs_fifo_probe(struct usbhs_priv *priv);
void usbhs_fifo_remove(struct usbhs_priv *priv);
void usbhs_fifo_init(struct usbhs_priv *priv);
void usbhs_fifo_quit(struct usbhs_priv *priv);

/*
 * packet info
 */
extern struct usbhs_pkt_handle usbhs_fifo_pio_push_handler;
extern struct usbhs_pkt_handle usbhs_fifo_pio_pop_handler;
extern struct usbhs_pkt_handle usbhs_ctrl_stage_end_handler;

extern struct usbhs_pkt_handle usbhs_fifo_dma_push_handler;
extern struct usbhs_pkt_handle usbhs_fifo_dma_pop_handler;

extern struct usbhs_pkt_handle usbhs_dcp_status_stage_in_handler;
extern struct usbhs_pkt_handle usbhs_dcp_status_stage_out_handler;

extern struct usbhs_pkt_handle usbhs_dcp_data_stage_in_handler;
extern struct usbhs_pkt_handle usbhs_dcp_data_stage_out_handler;

void usbhs_pkt_init(struct usbhs_pkt *pkt);
void usbhs_pkt_push(struct usbhs_pipe *pipe, struct usbhs_pkt *pkt,
		    void (*done)(struct usbhs_priv *priv,
				 struct usbhs_pkt *pkt),
		    void *buf, int len, int zero, int sequence);
struct usbhs_pkt *usbhs_pkt_pop(struct usbhs_pipe *pipe, struct usbhs_pkt *pkt);
void usbhs_pkt_start(struct usbhs_pipe *pipe);

#endif /* RENESAS_USB_FIFO_H */
