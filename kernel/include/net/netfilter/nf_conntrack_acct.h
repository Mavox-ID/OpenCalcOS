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
#ifndef _NF_CONNTRACK_ACCT_H
#define _NF_CONNTRACK_ACCT_H
#include <net/net_namespace.h>
#include <beep/netfilter/nf_conntrack_common.h>
#include <beep/netfilter/nf_conntrack_tuple_common.h>
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_extend.h>

struct nf_conn_counter {
	atomic64_t packets;
	atomic64_t bytes;
};

static inline
struct nf_conn_counter *nf_conn_acct_find(const struct nf_conn *ct)
{
	return nf_ct_ext_find(ct, NF_CT_EXT_ACCT);
}

static inline
struct nf_conn_counter *nf_ct_acct_ext_add(struct nf_conn *ct, gfp_t gfp)
{
	struct net *net = nf_ct_net(ct);
	struct nf_conn_counter *acct;

	if (!net->ct.sysctl_acct)
		return NULL;

	acct = nf_ct_ext_add(ct, NF_CT_EXT_ACCT, gfp);
	if (!acct)
		pr_debug("failed to add accounting extension area");


	return acct;
};

extern unsigned int
seq_print_acct(struct seq_file *s, const struct nf_conn *ct, int dir);

/* Check if connection tracking accounting is enabled */
static inline bool nf_ct_acct_enabled(struct net *net)
{
	return net->ct.sysctl_acct != 0;
}

/* Enable/disable connection tracking accounting */
static inline void nf_ct_set_acct(struct net *net, bool enable)
{
	net->ct.sysctl_acct = enable;
}

extern int nf_conntrack_acct_init(struct net *net);
extern void nf_conntrack_acct_fini(struct net *net);

#endif /* _NF_CONNTRACK_ACCT_H */
