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
#include <beep/spinlock.h>
#include <beep/netfilter/x_tables.h>
#include <beep/netfilter_bridge/ebtables.h>
#include <beep/netfilter_bridge/ebt_nflog.h>
#include <net/netfilter/nf_log.h>

static unsigned int
ebt_nflog_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct ebt_nflog_info *info = par->targinfo;
	struct nf_loginfo li;

	li.type = NF_LOG_TYPE_ULOG;
	li.u.ulog.copy_len = info->len;
	li.u.ulog.group = info->group;
	li.u.ulog.qthreshold = info->threshold;

	nf_log_packet(PF_BRIDGE, par->hooknum, skb, par->in, par->out,
	              &li, "%s", info->prefix);
	return EBT_CONTINUE;
}

static int ebt_nflog_tg_check(const struct xt_tgchk_param *par)
{
	struct ebt_nflog_info *info = par->targinfo;

	if (info->flags & ~EBT_NFLOG_MASK)
		return -EINVAL;
	info->prefix[EBT_NFLOG_PREFIX_SIZE - 1] = '\0';
	return 0;
}

static struct xt_target ebt_nflog_tg_reg __read_mostly = {
	.name       = "nflog",
	.revision   = 0,
	.family     = NFPROTO_BRIDGE,
	.target     = ebt_nflog_tg,
	.checkentry = ebt_nflog_tg_check,
	.targetsize = sizeof(struct ebt_nflog_info),
	.me         = THIS_MODULE,
};

static int __init ebt_nflog_init(void)
{
	return xt_register_target(&ebt_nflog_tg_reg);
}

static void __exit ebt_nflog_fini(void)
{
	xt_unregister_target(&ebt_nflog_tg_reg);
}

module_init(ebt_nflog_init);
module_exit(ebt_nflog_fini);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peter Warasin <peter@endian.com>");
MODULE_DESCRIPTION("ebtables NFLOG netfilter logging module");
