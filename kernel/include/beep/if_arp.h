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
#ifndef _BEEP_IF_ARP_H
#define _BEEP_IF_ARP_H

#include <beep/skbuff.h>
#include <uapi/beep/if_arp.h>

static inline struct arphdr *arp_hdr(const struct sk_buff *skb)
{
	return (struct arphdr *)skb_network_header(skb);
}

static inline int arp_hdr_len(struct net_device *dev)
{
	/* ARP header, plus 2 device addresses, plus 2 IP addresses. */
	return sizeof(struct arphdr) + (dev->addr_len + sizeof(u32)) * 2;
}
#endif	/* _BEEP_IF_ARP_H */
