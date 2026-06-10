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
#include <beep/netfilter/x_tables.h>
#include <beep/netfilter_bridge/ebtables.h>
#include <beep/netfilter_bridge/ebt_pkttype.h>

static bool
ebt_pkttype_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct ebt_pkttype_info *info = par->matchinfo;

	return (skb->pkt_type == info->pkt_type) ^ info->invert;
}

static int ebt_pkttype_mt_check(const struct xt_mtchk_param *par)
{
	const struct ebt_pkttype_info *info = par->matchinfo;

	if (info->invert != 0 && info->invert != 1)
		return -EINVAL;
	/* Allow any pkt_type value */
	return 0;
}

static struct xt_match ebt_pkttype_mt_reg __read_mostly = {
	.name		= "pkttype",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_pkttype_mt,
	.checkentry	= ebt_pkttype_mt_check,
	.matchsize	= sizeof(struct ebt_pkttype_info),
	.me		= THIS_MODULE,
};

static int __init ebt_pkttype_init(void)
{
	return xt_register_match(&ebt_pkttype_mt_reg);
}

static void __exit ebt_pkttype_fini(void)
{
	xt_unregister_match(&ebt_pkttype_mt_reg);
}

module_init(ebt_pkttype_init);
module_exit(ebt_pkttype_fini);
MODULE_DESCRIPTION("Ebtables: Link layer packet type match");
MODULE_LICENSE("GPL");
