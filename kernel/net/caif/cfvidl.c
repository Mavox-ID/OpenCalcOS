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
#define pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/slab.h>
#include <beep/errno.h>
#include <net/caif/caif_layer.h>
#include <net/caif/cfsrvl.h>
#include <net/caif/cfpkt.h>

#define container_obj(layr) ((struct cfsrvl *) layr)

static int cfvidl_receive(struct cflayer *layr, struct cfpkt *pkt);
static int cfvidl_transmit(struct cflayer *layr, struct cfpkt *pkt);

struct cflayer *cfvidl_create(u8 channel_id, struct dev_info *dev_info)
{
	struct cfsrvl *vid = kzalloc(sizeof(struct cfsrvl), GFP_ATOMIC);
	if (!vid)
		return NULL;
	caif_assert(offsetof(struct cfsrvl, layer) == 0);

	cfsrvl_init(vid, channel_id, dev_info, false);
	vid->layer.receive = cfvidl_receive;
	vid->layer.transmit = cfvidl_transmit;
	snprintf(vid->layer.name, CAIF_LAYER_NAME_SZ - 1, "vid1");
	return &vid->layer;
}

static int cfvidl_receive(struct cflayer *layr, struct cfpkt *pkt)
{
	u32 videoheader;
	if (cfpkt_extr_head(pkt, &videoheader, 4) < 0) {
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		return -EPROTO;
	}
	return layr->up->receive(layr->up, pkt);
}

static int cfvidl_transmit(struct cflayer *layr, struct cfpkt *pkt)
{
	struct cfsrvl *service = container_obj(layr);
	struct caif_payload_info *info;
	u32 videoheader = 0;
	int ret;

	if (!cfsrvl_ready(service, &ret)) {
		cfpkt_destroy(pkt);
		return ret;
	}

	cfpkt_add_head(pkt, &videoheader, 4);
	/* Add info for MUX-layer to route the packet out */
	info = cfpkt_info(pkt);
	info->channel_id = service->layer.id;
	info->dev_info = &service->dev_info;
	return layr->dn->transmit(layr->dn, pkt);
}
