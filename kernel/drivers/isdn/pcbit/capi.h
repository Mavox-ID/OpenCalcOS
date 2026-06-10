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
#ifndef CAPI_H
#define CAPI_H


#define REQ_CAUSE         0x01
#define REQ_DISPLAY       0x04
#define REQ_USER_TO_USER  0x08

#define AppInfoMask  REQ_CAUSE | REQ_DISPLAY | REQ_USER_TO_USER

/* Connection Setup */
extern int capi_conn_req(const char *calledPN, struct sk_buff **buf,
			 int proto);
extern int capi_decode_conn_conf(struct pcbit_chan *chan, struct sk_buff *skb,
				 int *complete);

extern int capi_decode_conn_ind(struct pcbit_chan *chan, struct sk_buff *skb,
				struct callb_data *info);
extern int capi_conn_resp(struct pcbit_chan *chan, struct sk_buff **skb);

extern int capi_conn_active_req(struct pcbit_chan *chan, struct sk_buff **skb);
extern int capi_decode_conn_actv_conf(struct pcbit_chan *chan,
				      struct sk_buff *skb);

extern int capi_decode_conn_actv_ind(struct pcbit_chan *chan,
				     struct sk_buff *skb);
extern int capi_conn_active_resp(struct pcbit_chan *chan,
				 struct sk_buff **skb);

/* Data */
extern int capi_select_proto_req(struct pcbit_chan *chan, struct sk_buff **skb,
				 int outgoing);
extern int capi_decode_sel_proto_conf(struct pcbit_chan *chan,
				      struct sk_buff *skb);

extern int capi_activate_transp_req(struct pcbit_chan *chan,
				    struct sk_buff **skb);
extern int capi_decode_actv_trans_conf(struct pcbit_chan *chan,
				       struct sk_buff *skb);

extern int capi_tdata_req(struct pcbit_chan *chan, struct sk_buff *skb);
extern int capi_tdata_resp(struct pcbit_chan *chan, struct sk_buff **skb);

/* Connection Termination */
extern int capi_disc_req(ushort callref, struct sk_buff **skb, u_char cause);

extern int capi_decode_disc_ind(struct pcbit_chan *chan, struct sk_buff *skb);
extern int capi_disc_resp(struct pcbit_chan *chan, struct sk_buff **skb);

#ifdef DEBUG
extern int capi_decode_debug_188(u_char *hdr, ushort hdrlen);
#endif

static inline struct pcbit_chan *
capi_channel(struct pcbit_dev *dev, struct sk_buff *skb)
{
	ushort callref;

	callref = *((ushort *)skb->data);
	skb_pull(skb, 2);

	if (dev->b1->callref == callref)
		return dev->b1;
	else if (dev->b2->callref == callref)
		return dev->b2;

	return NULL;
}

#endif
