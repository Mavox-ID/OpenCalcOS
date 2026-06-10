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
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/skbuff.h>
#include <beep/udp.h>

#include <net/netfilter/nf_conntrack_helper.h>
#include <net/netfilter/nf_conntrack_expect.h>
#include <net/netfilter/nf_nat_helper.h>
#include <beep/netfilter/nf_conntrack_amanda.h>

MODULE_AUTHOR("Brian J. Murrell <netfilter@interlinx.bc.ca>");
MODULE_DESCRIPTION("Amanda NAT helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ip_nat_amanda");

static unsigned int help(struct sk_buff *skb,
			 enum ip_conntrack_info ctinfo,
			 unsigned int protoff,
			 unsigned int matchoff,
			 unsigned int matchlen,
			 struct nf_conntrack_expect *exp)
{
	char buffer[sizeof("65535")];
	u_int16_t port;
	unsigned int ret;

	/* Connection comes from client. */
	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->dir = IP_CT_DIR_ORIGINAL;

	/* When you see the packet, we need to NAT it the same as the
	 * this one (ie. same IP: it will be TCP and master is UDP). */
	exp->expectfn = nf_nat_follow_master;

	/* Try to get same port: if not, try to change it. */
	for (port = ntohs(exp->saved_proto.tcp.port); port != 0; port++) {
		int res;

		exp->tuple.dst.u.tcp.port = htons(port);
		res = nf_ct_expect_related(exp);
		if (res == 0)
			break;
		else if (res != -EBUSY) {
			port = 0;
			break;
		}
	}

	if (port == 0)
		return NF_DROP;

	sprintf(buffer, "%u", port);
	ret = nf_nat_mangle_udp_packet(skb, exp->master, ctinfo,
				       protoff, matchoff, matchlen,
				       buffer, strlen(buffer));
	if (ret != NF_ACCEPT)
		nf_ct_unexpect_related(exp);
	return ret;
}

static void __exit nf_nat_amanda_fini(void)
{
	RCU_INIT_POINTER(nf_nat_amanda_hook, NULL);
	synchronize_rcu();
}

static int __init nf_nat_amanda_init(void)
{
	BUG_ON(nf_nat_amanda_hook != NULL);
	RCU_INIT_POINTER(nf_nat_amanda_hook, help);
	return 0;
}

module_init(nf_nat_amanda_init);
module_exit(nf_nat_amanda_fini);
