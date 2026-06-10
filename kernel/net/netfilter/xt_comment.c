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
#include <beep/netfilter/xt_comment.h>

MODULE_AUTHOR("Brad Fisher <brad@info-link.net>");
MODULE_DESCRIPTION("Xtables: No-op match which can be tagged with a comment");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_comment");
MODULE_ALIAS("ip6t_comment");

static bool
comment_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	/* We always match */
	return true;
}

static struct xt_match comment_mt_reg __read_mostly = {
	.name      = "comment",
	.revision  = 0,
	.family    = NFPROTO_UNSPEC,
	.match     = comment_mt,
	.matchsize = sizeof(struct xt_comment_info),
	.me        = THIS_MODULE,
};

static int __init comment_mt_init(void)
{
	return xt_register_match(&comment_mt_reg);
}

static void __exit comment_mt_exit(void)
{
	xt_unregister_match(&comment_mt_reg);
}

module_init(comment_mt_init);
module_exit(comment_mt_exit);
