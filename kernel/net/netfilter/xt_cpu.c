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
/*
 * Might be used to distribute connections on several daemons, if
 * RPS (Remote Packet Steering) is enabled or NIC is multiqueue capable,
 * each RX queue IRQ affined to one CPU (1:1 mapping)
 *
 */

/* (C) 2010 Eric Dumazet
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <beep/module.h>
#include <beep/skbuff.h>
#include <beep/netfilter/xt_cpu.h>
#include <beep/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eric Dumazet <eric.dumazet@gmail.com>");
MODULE_DESCRIPTION("Xtables: CPU match");
MODULE_ALIAS("ipt_cpu");
MODULE_ALIAS("ip6t_cpu");

static int cpu_mt_check(const struct xt_mtchk_param *par)
{
	const struct xt_cpu_info *info = par->matchinfo;

	if (info->invert & ~1)
		return -EINVAL;
	return 0;
}

static bool cpu_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_cpu_info *info = par->matchinfo;

	return (info->cpu == smp_processor_id()) ^ info->invert;
}

static struct xt_match cpu_mt_reg __read_mostly = {
	.name       = "cpu",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.checkentry = cpu_mt_check,
	.match      = cpu_mt,
	.matchsize  = sizeof(struct xt_cpu_info),
	.me         = THIS_MODULE,
};

static int __init cpu_mt_init(void)
{
	return xt_register_match(&cpu_mt_reg);
}

static void __exit cpu_mt_exit(void)
{
	xt_unregister_match(&cpu_mt_reg);
}

module_init(cpu_mt_init);
module_exit(cpu_mt_exit);
