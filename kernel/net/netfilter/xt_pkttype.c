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
#include <beep/module.h>
#include <beep/skbuff.h>
#include <beep/if_ether.h>
#include <beep/if_packet.h>
#include <beep/in.h>
#include <beep/ip.h>
#include <beep/ipv6.h>

#include <beep/netfilter/xt_pkttype.h>
#include <beep/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Ludvig <michal@logix.cz>");
MODULE_DESCRIPTION("Xtables: link layer packet type match");
MODULE_ALIAS("ipt_pkttype");
MODULE_ALIAS("ip6t_pkttype");

static bool
pkttype_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_pkttype_info *info = par->matchinfo;
	u_int8_t type;

	if (skb->pkt_type != PACKET_LOOPBACK)
		type = skb->pkt_type;
	else if (par->family == NFPROTO_IPV4 &&
	    ipv4_is_multicast(ip_hdr(skb)->daddr))
		type = PACKET_MULTICAST;
	else if (par->family == NFPROTO_IPV6 &&
	    ipv6_hdr(skb)->daddr.s6_addr[0] == 0xFF)
		type = PACKET_MULTICAST;
	else
		type = PACKET_BROADCAST;

	return (type == info->pkttype) ^ info->invert;
}

static struct xt_match pkttype_mt_reg __read_mostly = {
	.name      = "pkttype",
	.revision  = 0,
	.family    = NFPROTO_UNSPEC,
	.match     = pkttype_mt,
	.matchsize = sizeof(struct xt_pkttype_info),
	.me        = THIS_MODULE,
};

static int __init pkttype_mt_init(void)
{
	return xt_register_match(&pkttype_mt_reg);
}

static void __exit pkttype_mt_exit(void)
{
	xt_unregister_match(&pkttype_mt_reg);
}

module_init(pkttype_mt_init);
module_exit(pkttype_mt_exit);
