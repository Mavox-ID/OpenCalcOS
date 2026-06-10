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
#include <beep/udp.h>

#include <net/netfilter/nf_conntrack_helper.h>
#include <net/netfilter/nf_conntrack_expect.h>
#include <net/netfilter/nf_nat_helper.h>
#include <beep/netfilter/nf_conntrack_tftp.h>

MODULE_AUTHOR("Magnus Boden <mb@ozaba.mine.nu>");
MODULE_DESCRIPTION("TFTP NAT helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ip_nat_tftp");

static unsigned int help(struct sk_buff *skb,
			 enum ip_conntrack_info ctinfo,
			 struct nf_conntrack_expect *exp)
{
	const struct nf_conn *ct = exp->master;

	exp->saved_proto.udp.port
		= ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.udp.port;
	exp->dir = IP_CT_DIR_REPLY;
	exp->expectfn = nf_nat_follow_master;
	if (nf_ct_expect_related(exp) != 0)
		return NF_DROP;
	return NF_ACCEPT;
}

static void __exit nf_nat_tftp_fini(void)
{
	RCU_INIT_POINTER(nf_nat_tftp_hook, NULL);
	synchronize_rcu();
}

static int __init nf_nat_tftp_init(void)
{
	BUG_ON(nf_nat_tftp_hook != NULL);
	RCU_INIT_POINTER(nf_nat_tftp_hook, help);
	return 0;
}

module_init(nf_nat_tftp_init);
module_exit(nf_nat_tftp_fini);
