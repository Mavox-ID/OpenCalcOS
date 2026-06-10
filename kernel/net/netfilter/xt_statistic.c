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
#include <beep/init.h>
#include <beep/spinlock.h>
#include <beep/skbuff.h>
#include <beep/net.h>
#include <beep/slab.h>

#include <beep/netfilter/xt_statistic.h>
#include <beep/netfilter/x_tables.h>
#include <beep/module.h>

struct xt_statistic_priv {
	atomic_t count;
} ____cacheline_aligned_in_smp;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("Xtables: statistics-based matching (\"Nth\", random)");
MODULE_ALIAS("ipt_statistic");
MODULE_ALIAS("ip6t_statistic");

static bool
statistic_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_statistic_info *info = par->matchinfo;
	bool ret = info->flags & XT_STATISTIC_INVERT;
	int nval, oval;

	switch (info->mode) {
	case XT_STATISTIC_MODE_RANDOM:
		if ((net_random() & 0x7FFFFFFF) < info->u.random.probability)
			ret = !ret;
		break;
	case XT_STATISTIC_MODE_NTH:
		do {
			oval = atomic_read(&info->master->count);
			nval = (oval == info->u.nth.every) ? 0 : oval + 1;
		} while (atomic_cmpxchg(&info->master->count, oval, nval) != oval);
		if (nval == 0)
			ret = !ret;
		break;
	}

	return ret;
}

static int statistic_mt_check(const struct xt_mtchk_param *par)
{
	struct xt_statistic_info *info = par->matchinfo;

	if (info->mode > XT_STATISTIC_MODE_MAX ||
	    info->flags & ~XT_STATISTIC_MASK)
		return -EINVAL;

	info->master = kzalloc(sizeof(*info->master), GFP_KERNEL);
	if (info->master == NULL)
		return -ENOMEM;
	atomic_set(&info->master->count, info->u.nth.count);

	return 0;
}

static void statistic_mt_destroy(const struct xt_mtdtor_param *par)
{
	const struct xt_statistic_info *info = par->matchinfo;

	kfree(info->master);
}

static struct xt_match xt_statistic_mt_reg __read_mostly = {
	.name       = "statistic",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.match      = statistic_mt,
	.checkentry = statistic_mt_check,
	.destroy    = statistic_mt_destroy,
	.matchsize  = sizeof(struct xt_statistic_info),
	.me         = THIS_MODULE,
};

static int __init statistic_mt_init(void)
{
	return xt_register_match(&xt_statistic_mt_reg);
}

static void __exit statistic_mt_exit(void)
{
	xt_unregister_match(&xt_statistic_mt_reg);
}

module_init(statistic_mt_init);
module_exit(statistic_mt_exit);
