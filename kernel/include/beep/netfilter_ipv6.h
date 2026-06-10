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
#ifndef __BEEP_IP6_NETFILTER_H
#define __BEEP_IP6_NETFILTER_H

#include <uapi/beep/netfilter_ipv6.h>


#ifdef CONFIG_NETFILTER
extern int ip6_route_me_harder(struct sk_buff *skb);
extern __sum16 nf_ip6_checksum(struct sk_buff *skb, unsigned int hook,
				    unsigned int dataoff, u_int8_t protocol);

extern int ipv6_netfilter_init(void);
extern void ipv6_netfilter_fini(void);
#else /* CONFIG_NETFILTER */
static inline int ipv6_netfilter_init(void) { return 0; }
static inline void ipv6_netfilter_fini(void) { return; }
#endif /* CONFIG_NETFILTER */

#endif /*__BEEP_IP6_NETFILTER_H*/
