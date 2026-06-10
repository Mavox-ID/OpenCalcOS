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
/* (C) 2001-2002 Patrick McHardy <kaber@trash.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <beep/module.h>
#include <beep/skbuff.h>
#include <beep/ip.h>
#include <net/checksum.h>

#include <beep/netfilter_ipv4.h>
#include <beep/netfilter_ipv6.h>
#include <beep/netfilter/x_tables.h>
#include <beep/netfilter/xt_CLASSIFY.h>
#include <beep/netfilter_arp.h>

MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: Qdisc classification");
MODULE_ALIAS("ipt_CLASSIFY");
MODULE_ALIAS("ip6t_CLASSIFY");
MODULE_ALIAS("arpt_CLASSIFY");

static unsigned int
classify_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_classify_target_info *clinfo = par->targinfo;

	skb->priority = clinfo->priority;
	return XT_CONTINUE;
}

static struct xt_target classify_tg_reg[] __read_mostly = {
	{
		.name       = "CLASSIFY",
		.revision   = 0,
		.family     = NFPROTO_UNSPEC,
		.hooks      = (1 << NF_INET_LOCAL_OUT) | (1 << NF_INET_FORWARD) |
		              (1 << NF_INET_POST_ROUTING),
		.target     = classify_tg,
		.targetsize = sizeof(struct xt_classify_target_info),
		.me         = THIS_MODULE,
	},
	{
		.name       = "CLASSIFY",
		.revision   = 0,
		.family     = NFPROTO_ARP,
		.hooks      = (1 << NF_ARP_OUT) | (1 << NF_ARP_FORWARD),
		.target     = classify_tg,
		.targetsize = sizeof(struct xt_classify_target_info),
		.me         = THIS_MODULE,
	},
};

static int __init classify_tg_init(void)
{
	return xt_register_targets(classify_tg_reg, ARRAY_SIZE(classify_tg_reg));
}

static void __exit classify_tg_exit(void)
{
	xt_unregister_targets(classify_tg_reg, ARRAY_SIZE(classify_tg_reg));
}

module_init(classify_tg_init);
module_exit(classify_tg_exit);
