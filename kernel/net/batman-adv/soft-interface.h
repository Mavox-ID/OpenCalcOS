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
#ifndef _NET_BATMAN_ADV_SOFT_INTERFACE_H_
#define _NET_BATMAN_ADV_SOFT_INTERFACE_H_

int batadv_skb_head_push(struct sk_buff *skb, unsigned int len);
void batadv_interface_rx(struct net_device *soft_iface,
			 struct sk_buff *skb, struct batadv_hard_iface *recv_if,
			 int hdr_size, struct batadv_orig_node *orig_node);
struct net_device *batadv_softif_create(const char *name);
void batadv_softif_destroy(struct net_device *soft_iface);
int batadv_softif_is_valid(const struct net_device *net_dev);

#endif /* _NET_BATMAN_ADV_SOFT_INTERFACE_H_ */
