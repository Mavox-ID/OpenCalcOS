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
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <beep/types.h>
#include <beep/init.h>

#include <beep/netfilter.h>
#include <net/netfilter/nf_nat.h>
#include <net/netfilter/nf_nat_l4proto.h>

static bool unknown_in_range(const struct nf_conntrack_tuple *tuple,
			     enum nf_nat_manip_type manip_type,
			     const union nf_conntrack_man_proto *min,
			     const union nf_conntrack_man_proto *max)
{
	return true;
}

static void unknown_unique_tuple(const struct nf_nat_l3proto *l3proto,
				 struct nf_conntrack_tuple *tuple,
				 const struct nf_nat_range *range,
				 enum nf_nat_manip_type maniptype,
				 const struct nf_conn *ct)
{
	/* Sorry: we can't help you; if it's not unique, we can't frob
	 * anything.
	 */
	return;
}

static bool
unknown_manip_pkt(struct sk_buff *skb,
		  const struct nf_nat_l3proto *l3proto,
		  unsigned int iphdroff, unsigned int hdroff,
		  const struct nf_conntrack_tuple *tuple,
		  enum nf_nat_manip_type maniptype)
{
	return true;
}

const struct nf_nat_l4proto nf_nat_l4proto_unknown = {
	.manip_pkt		= unknown_manip_pkt,
	.in_range		= unknown_in_range,
	.unique_tuple		= unknown_unique_tuple,
};
