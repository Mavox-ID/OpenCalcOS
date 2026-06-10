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
#ifndef RENESAS_USB_PIPE_H
#define RENESAS_USB_PIPE_H

#include "common.h"
#include "fifo.h"

/*
 *	struct
 */
struct usbhs_pipe {
	u32 pipe_type;	/* USB_ENDPOINT_XFER_xxx */

	struct usbhs_priv *priv;
	struct usbhs_fifo *fifo;
	struct list_head list;

	int maxp;

	u32 flags;
#define USBHS_PIPE_FLAGS_IS_USED		(1 << 0)
#define USBHS_PIPE_FLAGS_IS_DIR_IN		(1 << 1)
#define USBHS_PIPE_FLAGS_IS_DIR_HOST		(1 << 2)

	struct usbhs_pkt_handle *handler;

	void *mod_private;
};

struct usbhs_pipe_info {
	struct usbhs_pipe *pipe;
	int size;	/* array size of "pipe" */
	int bufnmb_last;	/* FIXME : driver needs good allocator */

	int (*dma_map_ctrl)(struct usbhs_pkt *pkt, int map);
};

/*
 * pipe list
 */
#define __usbhs_for_each_pipe(start, pos, info, i)	\
	for (i = start, pos = (info)->pipe + i;		\
	     i < (info)->size;				\
	     i++, pos = (info)->pipe + i)

#define usbhs_for_each_pipe(pos, priv, i)			\
	__usbhs_for_each_pipe(1, pos, &((priv)->pipe_info), i)

#define usbhs_for_each_pipe_with_dcp(pos, priv, i)		\
	__usbhs_for_each_pipe(0, pos, &((priv)->pipe_info), i)

/*
 * data
 */
#define usbhs_priv_to_pipeinfo(pr)	(&(pr)->pipe_info)

/*
 * pipe control
 */
char *usbhs_pipe_name(struct usbhs_pipe *pipe);
struct usbhs_pipe
*usbhs_pipe_malloc(struct usbhs_priv *priv, int endpoint_type, int dir_in);
int usbhs_pipe_probe(struct usbhs_priv *priv);
void usbhs_pipe_remove(struct usbhs_priv *priv);
int usbhs_pipe_is_dir_in(struct usbhs_pipe *pipe);
int usbhs_pipe_is_dir_host(struct usbhs_pipe *pipe);
void usbhs_pipe_init(struct usbhs_priv *priv,
		     int (*dma_map_ctrl)(struct usbhs_pkt *pkt, int map));
int usbhs_pipe_get_maxpacket(struct usbhs_pipe *pipe);
void usbhs_pipe_clear(struct usbhs_pipe *pipe);
int usbhs_pipe_is_accessible(struct usbhs_pipe *pipe);
void usbhs_pipe_enable(struct usbhs_pipe *pipe);
void usbhs_pipe_disable(struct usbhs_pipe *pipe);
void usbhs_pipe_stall(struct usbhs_pipe *pipe);
int usbhs_pipe_is_stall(struct usbhs_pipe *pipe);
void usbhs_pipe_set_trans_count_if_bulk(struct usbhs_pipe *pipe, int len);
void usbhs_pipe_select_fifo(struct usbhs_pipe *pipe, struct usbhs_fifo *fifo);
void usbhs_pipe_config_update(struct usbhs_pipe *pipe, u16 devsel,
			      u16 epnum, u16 maxp);

#define usbhs_pipe_sequence_data0(pipe)	usbhs_pipe_data_sequence(pipe, 0)
#define usbhs_pipe_sequence_data1(pipe)	usbhs_pipe_data_sequence(pipe, 1)
void usbhs_pipe_data_sequence(struct usbhs_pipe *pipe, int data);

#define usbhs_pipe_to_priv(p)	((p)->priv)
#define usbhs_pipe_number(p)	(int)((p) - (p)->priv->pipe_info.pipe)
#define usbhs_pipe_is_dcp(p)	((p)->priv->pipe_info.pipe == (p))
#define usbhs_pipe_to_fifo(p)	((p)->fifo)
#define usbhs_pipe_is_busy(p)	usbhs_pipe_to_fifo(p)

#define usbhs_pipe_type(p)		((p)->pipe_type)
#define usbhs_pipe_type_is(p, t)	((p)->pipe_type == t)

/*
 * dcp control
 */
struct usbhs_pipe *usbhs_dcp_malloc(struct usbhs_priv *priv);
void usbhs_dcp_control_transfer_done(struct usbhs_pipe *pipe);
void usbhs_dcp_dir_for_host(struct usbhs_pipe *pipe, int dir_out);

#endif /* RENESAS_USB_PIPE_H */
