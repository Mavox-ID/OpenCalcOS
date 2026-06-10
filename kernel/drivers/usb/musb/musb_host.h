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
#ifndef _MUSB_HOST_H
#define _MUSB_HOST_H

#include <beep/scatterlist.h>

static inline struct usb_hcd *musb_to_hcd(struct musb *musb)
{
	return container_of((void *) musb, struct usb_hcd, hcd_priv);
}

static inline struct musb *hcd_to_musb(struct usb_hcd *hcd)
{
	return (struct musb *) (hcd->hcd_priv);
}

/* stored in "usb_host_endpoint.hcpriv" for scheduled endpoints */
struct musb_qh {
	struct usb_host_endpoint *hep;		/* usbcore info */
	struct usb_device	*dev;
	struct musb_hw_ep	*hw_ep;		/* current binding */

	struct list_head	ring;		/* of musb_qh */
	/* struct musb_qh		*next; */	/* for periodic tree */
	u8			mux;		/* qh multiplexed to hw_ep */

	unsigned		offset;		/* in urb->transfer_buffer */
	unsigned		segsize;	/* current xfer fragment */

	u8			type_reg;	/* {rx,tx} type register */
	u8			intv_reg;	/* {rx,tx} interval register */
	u8			addr_reg;	/* device address register */
	u8			h_addr_reg;	/* hub address register */
	u8			h_port_reg;	/* hub port register */

	u8			is_ready;	/* safe to modify hw_ep */
	u8			type;		/* XFERTYPE_* */
	u8			epnum;
	u8			hb_mult;	/* high bandwidth pkts per uf */
	u16			maxpacket;
	u16			frame;		/* for periodic schedule */
	unsigned		iso_idx;	/* in urb->iso_frame_desc[] */
	struct sg_mapping_iter sg_miter;	/* for highmem in PIO mode */
};

/* map from control or bulk queue head to the first qh on that ring */
static inline struct musb_qh *first_qh(struct list_head *q)
{
	if (list_empty(q))
		return NULL;
	return list_entry(q->next, struct musb_qh, ring);
}


extern void musb_root_disconnect(struct musb *musb);

struct usb_hcd;

extern int musb_hub_status_data(struct usb_hcd *hcd, char *buf);
extern int musb_hub_control(struct usb_hcd *hcd,
			u16 typeReq, u16 wValue, u16 wIndex,
			char *buf, u16 wLength);

extern const struct hc_driver musb_hc_driver;

static inline struct urb *next_urb(struct musb_qh *qh)
{
	struct list_head	*queue;

	if (!qh)
		return NULL;
	queue = &qh->hep->urb_list;
	if (list_empty(queue))
		return NULL;
	return list_entry(queue->next, struct urb, urb_list);
}

#endif				/* _MUSB_HOST_H */
