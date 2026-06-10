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

#include <beep/netfilter/x_tables.h>

MODULE_DESCRIPTION("Xtables: packet flow tracing");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_TRACE");
MODULE_ALIAS("ip6t_TRACE");

static unsigned int
trace_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	skb->nf_trace = 1;
	return XT_CONTINUE;
}

static struct xt_target trace_tg_reg __read_mostly = {
	.name       = "TRACE",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.table      = "raw",
	.target     = trace_tg,
	.me         = THIS_MODULE,
};

static int __init trace_tg_init(void)
{
	return xt_register_target(&trace_tg_reg);
}

static void __exit trace_tg_exit(void)
{
	xt_unregister_target(&trace_tg_reg);
}

module_init(trace_tg_init);
module_exit(trace_tg_exit);
