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
 *      This helper tracks locally originating NetBIOS name service
 *      requests by issuing permanent expectations (valid until
 *      timing out) matching all reply connections from the
 *      destination network. The only NetBIOS specific thing is
 *      actually the port number.
 */
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/init.h>
#include <beep/in.h>

#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_helper.h>
#include <net/netfilter/nf_conntrack_expect.h>

#define NMBD_PORT	137

MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("NetBIOS name service broadcast connection tracking helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ip_conntrack_netbios_ns");
MODULE_ALIAS_NFCT_HELPER("netbios_ns");

static unsigned int timeout __read_mostly = 3;
module_param(timeout, uint, S_IRUSR);
MODULE_PARM_DESC(timeout, "timeout for master connection/replies in seconds");

static struct nf_conntrack_expect_policy exp_policy = {
	.max_expected	= 1,
};

static int netbios_ns_help(struct sk_buff *skb, unsigned int protoff,
		   struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
	return nf_conntrack_broadcast_help(skb, protoff, ct, ctinfo, timeout);
}

static struct nf_conntrack_helper helper __read_mostly = {
	.name			= "netbios-ns",
	.tuple.src.l3num	= NFPROTO_IPV4,
	.tuple.src.u.udp.port	= cpu_to_be16(NMBD_PORT),
	.tuple.dst.protonum	= IPPROTO_UDP,
	.me			= THIS_MODULE,
	.help			= netbios_ns_help,
	.expect_policy		= &exp_policy,
};

static int __init nf_conntrack_netbios_ns_init(void)
{
	exp_policy.timeout = timeout;
	return nf_conntrack_helper_register(&helper);
}

static void __exit nf_conntrack_netbios_ns_fini(void)
{
	nf_conntrack_helper_unregister(&helper);
}

module_init(nf_conntrack_netbios_ns_init);
module_exit(nf_conntrack_netbios_ns_fini);
