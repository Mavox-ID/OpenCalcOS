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
#include <beep/netfilter.h>
#include <beep/netfilter/x_tables.h>
#include <net/netfilter/nf_nat_core.h>

static int xt_nat_checkentry_v0(const struct xt_tgchk_param *par)
{
	const struct nf_nat_ipv4_multi_range_compat *mr = par->targinfo;

	if (mr->rangesize != 1) {
		pr_info("%s: multiple ranges no longer supported\n",
			par->target->name);
		return -EINVAL;
	}
	return 0;
}

static void xt_nat_convert_range(struct nf_nat_range *dst,
				 const struct nf_nat_ipv4_range *src)
{
	memset(&dst->min_addr, 0, sizeof(dst->min_addr));
	memset(&dst->max_addr, 0, sizeof(dst->max_addr));

	dst->flags	 = src->flags;
	dst->min_addr.ip = src->min_ip;
	dst->max_addr.ip = src->max_ip;
	dst->min_proto	 = src->min;
	dst->max_proto	 = src->max;
}

static unsigned int
xt_snat_target_v0(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct nf_nat_ipv4_multi_range_compat *mr = par->targinfo;
	struct nf_nat_range range;
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	NF_CT_ASSERT(ct != NULL &&
		     (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
		      ctinfo == IP_CT_RELATED_REPLY));

	xt_nat_convert_range(&range, &mr->range[0]);
	return nf_nat_setup_info(ct, &range, NF_NAT_MANIP_SRC);
}

static unsigned int
xt_dnat_target_v0(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct nf_nat_ipv4_multi_range_compat *mr = par->targinfo;
	struct nf_nat_range range;
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	NF_CT_ASSERT(ct != NULL &&
		     (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED));

	xt_nat_convert_range(&range, &mr->range[0]);
	return nf_nat_setup_info(ct, &range, NF_NAT_MANIP_DST);
}

static unsigned int
xt_snat_target_v1(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct nf_nat_range *range = par->targinfo;
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	NF_CT_ASSERT(ct != NULL &&
		     (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
		      ctinfo == IP_CT_RELATED_REPLY));

	return nf_nat_setup_info(ct, range, NF_NAT_MANIP_SRC);
}

static unsigned int
xt_dnat_target_v1(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct nf_nat_range *range = par->targinfo;
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	NF_CT_ASSERT(ct != NULL &&
		     (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED));

	return nf_nat_setup_info(ct, range, NF_NAT_MANIP_DST);
}

static struct xt_target xt_nat_target_reg[] __read_mostly = {
	{
		.name		= "SNAT",
		.revision	= 0,
		.checkentry	= xt_nat_checkentry_v0,
		.target		= xt_snat_target_v0,
		.targetsize	= sizeof(struct nf_nat_ipv4_multi_range_compat),
		.family		= NFPROTO_IPV4,
		.table		= "nat",
		.hooks		= (1 << NF_INET_POST_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	},
	{
		.name		= "DNAT",
		.revision	= 0,
		.checkentry	= xt_nat_checkentry_v0,
		.target		= xt_dnat_target_v0,
		.targetsize	= sizeof(struct nf_nat_ipv4_multi_range_compat),
		.family		= NFPROTO_IPV4,
		.table		= "nat",
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_OUT),
		.me		= THIS_MODULE,
	},
	{
		.name		= "SNAT",
		.revision	= 1,
		.target		= xt_snat_target_v1,
		.targetsize	= sizeof(struct nf_nat_range),
		.table		= "nat",
		.hooks		= (1 << NF_INET_POST_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	},
	{
		.name		= "DNAT",
		.revision	= 1,
		.target		= xt_dnat_target_v1,
		.targetsize	= sizeof(struct nf_nat_range),
		.table		= "nat",
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_OUT),
		.me		= THIS_MODULE,
	},
};

static int __init xt_nat_init(void)
{
	return xt_register_targets(xt_nat_target_reg,
				   ARRAY_SIZE(xt_nat_target_reg));
}

static void __exit xt_nat_exit(void)
{
	xt_unregister_targets(xt_nat_target_reg, ARRAY_SIZE(xt_nat_target_reg));
}

module_init(xt_nat_init);
module_exit(xt_nat_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_ALIAS("ipt_SNAT");
MODULE_ALIAS("ipt_DNAT");
MODULE_ALIAS("ip6t_SNAT");
MODULE_ALIAS("ip6t_DNAT");
