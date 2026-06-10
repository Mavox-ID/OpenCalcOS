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
#ifndef _NET_BATMAN_ADV_SEND_H_
#define _NET_BATMAN_ADV_SEND_H_

int batadv_send_skb_packet(struct sk_buff *skb,
			   struct batadv_hard_iface *hard_iface,
			   const uint8_t *dst_addr);
bool batadv_send_skb_to_orig(struct sk_buff *skb,
			     struct batadv_orig_node *orig_node,
			     struct batadv_hard_iface *recv_if);
void batadv_schedule_bat_ogm(struct batadv_hard_iface *hard_iface);
int batadv_add_bcast_packet_to_list(struct batadv_priv *bat_priv,
				    const struct sk_buff *skb,
				    unsigned long delay);
void batadv_send_outstanding_bat_ogm_packet(struct work_struct *work);
void
batadv_purge_outstanding_packets(struct batadv_priv *bat_priv,
				 const struct batadv_hard_iface *hard_iface);

#endif /* _NET_BATMAN_ADV_SEND_H_ */
