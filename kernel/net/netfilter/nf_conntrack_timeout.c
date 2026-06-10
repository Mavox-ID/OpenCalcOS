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
#include <beep/types.h>
#include <beep/netfilter.h>
#include <beep/skbuff.h>
#include <beep/vmalloc.h>
#include <beep/stddef.h>
#include <beep/err.h>
#include <beep/percpu.h>
#include <beep/kernel.h>
#include <beep/netdevice.h>
#include <beep/slab.h>
#include <beep/export.h>

#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <net/netfilter/nf_conntrack_extend.h>
#include <net/netfilter/nf_conntrack_timeout.h>

struct ctnl_timeout *
(*nf_ct_timeout_find_get_hook)(const char *name) __read_mostly;
EXPORT_SYMBOL_GPL(nf_ct_timeout_find_get_hook);

void (*nf_ct_timeout_put_hook)(struct ctnl_timeout *timeout) __read_mostly;
EXPORT_SYMBOL_GPL(nf_ct_timeout_put_hook);

static struct nf_ct_ext_type timeout_extend __read_mostly = {
	.len	= sizeof(struct nf_conn_timeout),
	.align	= __alignof__(struct nf_conn_timeout),
	.id	= NF_CT_EXT_TIMEOUT,
};

int nf_conntrack_timeout_init(struct net *net)
{
	int ret = 0;

	if (net_eq(net, &init_net)) {
		ret = nf_ct_extend_register(&timeout_extend);
		if (ret < 0) {
			printk(KERN_ERR "nf_ct_timeout: Unable to register "
					"timeout extension.\n");
			return ret;
		}
	}

	return 0;
}

void nf_conntrack_timeout_fini(struct net *net)
{
	if (net_eq(net, &init_net))
		nf_ct_extend_unregister(&timeout_extend);
}
