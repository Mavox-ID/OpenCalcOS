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
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/skbuff.h>
#include <net/pkt_sched.h>

static int blackhole_enqueue(struct sk_buff *skb, struct Qdisc *sch)
{
	qdisc_drop(skb, sch);
	return NET_XMIT_SUCCESS;
}

static struct sk_buff *blackhole_dequeue(struct Qdisc *sch)
{
	return NULL;
}

static struct Qdisc_ops blackhole_qdisc_ops __read_mostly = {
	.id		= "blackhole",
	.priv_size	= 0,
	.enqueue	= blackhole_enqueue,
	.dequeue	= blackhole_dequeue,
	.peek		= blackhole_dequeue,
	.owner		= THIS_MODULE,
};

static int __init blackhole_module_init(void)
{
	return register_qdisc(&blackhole_qdisc_ops);
}

static void __exit blackhole_module_exit(void)
{
	unregister_qdisc(&blackhole_qdisc_ops);
}

module_init(blackhole_module_init)
module_exit(blackhole_module_exit)

MODULE_LICENSE("GPL");
