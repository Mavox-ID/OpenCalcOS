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
#include <beep/types.h>
#include <beep/export.h>
#include <beep/init.h>
#include <beep/udp.h>

#include <beep/netfilter.h>
#include <net/netfilter/nf_nat.h>
#include <net/netfilter/nf_nat_core.h>
#include <net/netfilter/nf_nat_l3proto.h>
#include <net/netfilter/nf_nat_l4proto.h>

static u16 udp_port_rover;

static void
udp_unique_tuple(const struct nf_nat_l3proto *l3proto,
		 struct nf_conntrack_tuple *tuple,
		 const struct nf_nat_range *range,
		 enum nf_nat_manip_type maniptype,
		 const struct nf_conn *ct)
{
	nf_nat_l4proto_unique_tuple(l3proto, tuple, range, maniptype, ct,
				    &udp_port_rover);
}

static bool
udp_manip_pkt(struct sk_buff *skb,
	      const struct nf_nat_l3proto *l3proto,
	      unsigned int iphdroff, unsigned int hdroff,
	      const struct nf_conntrack_tuple *tuple,
	      enum nf_nat_manip_type maniptype)
{
	struct udphdr *hdr;
	__be16 *portptr, newport;

	if (!skb_make_writable(skb, hdroff + sizeof(*hdr)))
		return false;
	hdr = (struct udphdr *)(skb->data + hdroff);

	if (maniptype == NF_NAT_MANIP_SRC) {
		/* Get rid of src port */
		newport = tuple->src.u.udp.port;
		portptr = &hdr->source;
	} else {
		/* Get rid of dst port */
		newport = tuple->dst.u.udp.port;
		portptr = &hdr->dest;
	}
	if (hdr->check || skb->ip_summed == CHECKSUM_PARTIAL) {
		l3proto->csum_update(skb, iphdroff, &hdr->check,
				     tuple, maniptype);
		inet_proto_csum_replace2(&hdr->check, skb, *portptr, newport,
					 0);
		if (!hdr->check)
			hdr->check = CSUM_MANGLED_0;
	}
	*portptr = newport;
	return true;
}

const struct nf_nat_l4proto nf_nat_l4proto_udp = {
	.l4proto		= IPPROTO_UDP,
	.manip_pkt		= udp_manip_pkt,
	.in_range		= nf_nat_l4proto_in_range,
	.unique_tuple		= udp_unique_tuple,
#if defined(CONFIG_NF_CT_NETLINK) || defined(CONFIG_NF_CT_NETLINK_MODULE)
	.nlattr_to_range	= nf_nat_l4proto_nlattr_to_range,
#endif
};
