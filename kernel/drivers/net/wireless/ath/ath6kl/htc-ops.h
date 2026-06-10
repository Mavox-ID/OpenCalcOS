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
#ifndef HTC_OPS_H
#define HTC_OPS_H

#include "htc.h"
#include "debug.h"

static inline void *ath6kl_htc_create(struct ath6kl *ar)
{
	return ar->htc_ops->create(ar);
}

static inline int ath6kl_htc_wait_target(struct htc_target *target)
{
	return target->dev->ar->htc_ops->wait_target(target);
}

static inline int ath6kl_htc_start(struct htc_target *target)
{
	return target->dev->ar->htc_ops->start(target);
}

static inline int ath6kl_htc_conn_service(struct htc_target *target,
					  struct htc_service_connect_req *req,
					  struct htc_service_connect_resp *resp)
{
	return target->dev->ar->htc_ops->conn_service(target, req, resp);
}

static inline int ath6kl_htc_tx(struct htc_target *target,
				struct htc_packet *packet)
{
	return target->dev->ar->htc_ops->tx(target, packet);
}

static inline void ath6kl_htc_stop(struct htc_target *target)
{
	return target->dev->ar->htc_ops->stop(target);
}

static inline void ath6kl_htc_cleanup(struct htc_target *target)
{
	return target->dev->ar->htc_ops->cleanup(target);
}

static inline void ath6kl_htc_flush_txep(struct htc_target *target,
					 enum htc_endpoint_id endpoint,
					 u16 tag)
{
	return target->dev->ar->htc_ops->flush_txep(target, endpoint, tag);
}

static inline void ath6kl_htc_flush_rx_buf(struct htc_target *target)
{
	return target->dev->ar->htc_ops->flush_rx_buf(target);
}

static inline void ath6kl_htc_activity_changed(struct htc_target *target,
					       enum htc_endpoint_id endpoint,
					       bool active)
{
	return target->dev->ar->htc_ops->activity_changed(target, endpoint,
							  active);
}

static inline int ath6kl_htc_get_rxbuf_num(struct htc_target *target,
					   enum htc_endpoint_id endpoint)
{
	return target->dev->ar->htc_ops->get_rxbuf_num(target, endpoint);
}

static inline int ath6kl_htc_add_rxbuf_multiple(struct htc_target *target,
						struct list_head *pktq)
{
	return target->dev->ar->htc_ops->add_rxbuf_multiple(target, pktq);
}

static inline int ath6kl_htc_credit_setup(struct htc_target *target,
					  struct ath6kl_htc_credit_info *info)
{
	return target->dev->ar->htc_ops->credit_setup(target, info);
}

static inline void ath6kl_htc_tx_complete(struct ath6kl *ar,
					  struct sk_buff *skb)
{
	ar->htc_ops->tx_complete(ar, skb);
}


static inline void ath6kl_htc_rx_complete(struct ath6kl *ar,
					  struct sk_buff *skb, u8 pipe)
{
	ar->htc_ops->rx_complete(ar, skb, pipe);
}


#endif
