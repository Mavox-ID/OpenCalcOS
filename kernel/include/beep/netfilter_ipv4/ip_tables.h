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
 * 	Format of an IP firewall descriptor
 *
 * 	src, dst, src_mask, dst_mask are always stored in network byte order.
 * 	flags are stored in host byte order (of course).
 * 	Port numbers are stored in HOST byte order.
 */
#ifndef _IPTABLES_H
#define _IPTABLES_H

#include <beep/if.h>
#include <beep/in.h>
#include <beep/ip.h>
#include <beep/skbuff.h>

#include <beep/init.h>
#include <uapi/beep/netfilter_ipv4/ip_tables.h>

extern void ipt_init(void) __init;

extern struct xt_table *ipt_register_table(struct net *net,
					   const struct xt_table *table,
					   const struct ipt_replace *repl);
extern void ipt_unregister_table(struct net *net, struct xt_table *table);

/* Standard entry. */
struct ipt_standard {
	struct ipt_entry entry;
	struct xt_standard_target target;
};

struct ipt_error {
	struct ipt_entry entry;
	struct xt_error_target target;
};

#define IPT_ENTRY_INIT(__size)						       \
{									       \
	.target_offset	= sizeof(struct ipt_entry),			       \
	.next_offset	= (__size),					       \
}

#define IPT_STANDARD_INIT(__verdict)					       \
{									       \
	.entry		= IPT_ENTRY_INIT(sizeof(struct ipt_standard)),	       \
	.target		= XT_TARGET_INIT(XT_STANDARD_TARGET,		       \
					 sizeof(struct xt_standard_target)),   \
	.target.verdict	= -(__verdict) - 1,				       \
}

#define IPT_ERROR_INIT							       \
{									       \
	.entry		= IPT_ENTRY_INIT(sizeof(struct ipt_error)),	       \
	.target		= XT_TARGET_INIT(XT_ERROR_TARGET,		       \
					 sizeof(struct xt_error_target)),      \
	.target.errorname = "ERROR",					       \
}

extern void *ipt_alloc_initial_table(const struct xt_table *);
extern unsigned int ipt_do_table(struct sk_buff *skb,
				 unsigned int hook,
				 const struct net_device *in,
				 const struct net_device *out,
				 struct xt_table *table);

#ifdef CONFIG_COMPAT
#include <net/compat.h>

struct compat_ipt_entry {
	struct ipt_ip ip;
	compat_uint_t nfcache;
	__u16 target_offset;
	__u16 next_offset;
	compat_uint_t comefrom;
	struct compat_xt_counters counters;
	unsigned char elems[0];
};

/* Helper functions */
static inline struct xt_entry_target *
compat_ipt_get_target(struct compat_ipt_entry *e)
{
	return (void *)e + e->target_offset;
}

#endif /* CONFIG_COMPAT */
#endif /* _IPTABLES_H */
