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
#ifndef _NET_BATMAN_ADV_ROUTING_H_
#define _NET_BATMAN_ADV_ROUTING_H_

void batadv_slide_own_bcast_window(struct batadv_hard_iface *hard_iface);
bool batadv_check_management_packet(struct sk_buff *skb,
				    struct batadv_hard_iface *hard_iface,
				    int header_len);
void batadv_update_route(struct batadv_priv *bat_priv,
			 struct batadv_orig_node *orig_node,
			 struct batadv_neigh_node *neigh_node);
int batadv_recv_icmp_packet(struct sk_buff *skb,
			    struct batadv_hard_iface *recv_if);
int batadv_recv_unicast_packet(struct sk_buff *skb,
			       struct batadv_hard_iface *recv_if);
int batadv_recv_ucast_frag_packet(struct sk_buff *skb,
				  struct batadv_hard_iface *recv_if);
int batadv_recv_bcast_packet(struct sk_buff *skb,
			     struct batadv_hard_iface *recv_if);
int batadv_recv_vis_packet(struct sk_buff *skb,
			   struct batadv_hard_iface *recv_if);
int batadv_recv_tt_query(struct sk_buff *skb,
			 struct batadv_hard_iface *recv_if);
int batadv_recv_roam_adv(struct sk_buff *skb,
			 struct batadv_hard_iface *recv_if);
struct batadv_neigh_node *
batadv_find_router(struct batadv_priv *bat_priv,
		   struct batadv_orig_node *orig_node,
		   const struct batadv_hard_iface *recv_if);
void batadv_bonding_candidate_del(struct batadv_orig_node *orig_node,
				  struct batadv_neigh_node *neigh_node);
void batadv_bonding_candidate_add(struct batadv_orig_node *orig_node,
				  struct batadv_neigh_node *neigh_node);
void batadv_bonding_save_primary(const struct batadv_orig_node *orig_node,
				 struct batadv_orig_node *orig_neigh_node,
				 const struct batadv_ogm_packet
				 *batman_ogm_packet);
int batadv_window_protected(struct batadv_priv *bat_priv, int32_t seq_num_diff,
			    unsigned long *last_reset);

#endif /* _NET_BATMAN_ADV_ROUTING_H_ */
