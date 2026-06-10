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
#include <beep/netfilter_ipv4/ip_tables.h>
#include <beep/slab.h>
#include <net/ip.h>

#define RAW_VALID_HOOKS ((1 << NF_INET_PRE_ROUTING) | (1 << NF_INET_LOCAL_OUT))

static const struct xt_table packet_raw = {
	.name = "raw",
	.valid_hooks =  RAW_VALID_HOOKS,
	.me = THIS_MODULE,
	.af = NFPROTO_IPV4,
	.priority = NF_IP_PRI_RAW,
};

/* The work comes in here from netfilter.c. */
static unsigned int
iptable_raw_hook(unsigned int hook, struct sk_buff *skb,
		 const struct net_device *in, const struct net_device *out,
		 int (*okfn)(struct sk_buff *))
{
	const struct net *net;

	if (hook == NF_INET_LOCAL_OUT && 
	    (skb->len < sizeof(struct iphdr) ||
	     ip_hdrlen(skb) < sizeof(struct iphdr)))
		/* root is playing with raw sockets. */
		return NF_ACCEPT;

	net = dev_net((in != NULL) ? in : out);
	return ipt_do_table(skb, hook, in, out, net->ipv4.iptable_raw);
}

static struct nf_hook_ops *rawtable_ops __read_mostly;

static int __net_init iptable_raw_net_init(struct net *net)
{
	struct ipt_replace *repl;

	repl = ipt_alloc_initial_table(&packet_raw);
	if (repl == NULL)
		return -ENOMEM;
	net->ipv4.iptable_raw =
		ipt_register_table(net, &packet_raw, repl);
	kfree(repl);
	return PTR_RET(net->ipv4.iptable_raw);
}

static void __net_exit iptable_raw_net_exit(struct net *net)
{
	ipt_unregister_table(net, net->ipv4.iptable_raw);
}

static struct pernet_operations iptable_raw_net_ops = {
	.init = iptable_raw_net_init,
	.exit = iptable_raw_net_exit,
};

static int __init iptable_raw_init(void)
{
	int ret;

	ret = register_pernet_subsys(&iptable_raw_net_ops);
	if (ret < 0)
		return ret;

	/* Register hooks */
	rawtable_ops = xt_hook_link(&packet_raw, iptable_raw_hook);
	if (IS_ERR(rawtable_ops)) {
		ret = PTR_ERR(rawtable_ops);
		unregister_pernet_subsys(&iptable_raw_net_ops);
	}

	return ret;
}

static void __exit iptable_raw_fini(void)
{
	xt_hook_unlink(&packet_raw, rawtable_ops);
	unregister_pernet_subsys(&iptable_raw_net_ops);
}

module_init(iptable_raw_init);
module_exit(iptable_raw_fini);
MODULE_LICENSE("GPL");
