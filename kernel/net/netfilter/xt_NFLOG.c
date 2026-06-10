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
#include <beep/init.h>
#include <beep/skbuff.h>

#include <beep/netfilter/x_tables.h>
#include <beep/netfilter/xt_NFLOG.h>
#include <net/netfilter/nf_log.h>
#include <net/netfilter/nfnetlink_log.h>

MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("Xtables: packet logging to netlink using NFLOG");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_NFLOG");
MODULE_ALIAS("ip6t_NFLOG");

static unsigned int
nflog_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_nflog_info *info = par->targinfo;
	struct nf_loginfo li;

	li.type		     = NF_LOG_TYPE_ULOG;
	li.u.ulog.copy_len   = info->len;
	li.u.ulog.group	     = info->group;
	li.u.ulog.qthreshold = info->threshold;

	nfulnl_log_packet(par->family, par->hooknum, skb, par->in,
			  par->out, &li, info->prefix);
	return XT_CONTINUE;
}

static int nflog_tg_check(const struct xt_tgchk_param *par)
{
	const struct xt_nflog_info *info = par->targinfo;

	if (info->flags & ~XT_NFLOG_MASK)
		return -EINVAL;
	if (info->prefix[sizeof(info->prefix) - 1] != '\0')
		return -EINVAL;
	return 0;
}

static struct xt_target nflog_tg_reg __read_mostly = {
	.name       = "NFLOG",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.checkentry = nflog_tg_check,
	.target     = nflog_tg,
	.targetsize = sizeof(struct xt_nflog_info),
	.me         = THIS_MODULE,
};

static int __init nflog_tg_init(void)
{
	return xt_register_target(&nflog_tg_reg);
}

static void __exit nflog_tg_exit(void)
{
	xt_unregister_target(&nflog_tg_reg);
}

module_init(nflog_tg_init);
module_exit(nflog_tg_exit);
