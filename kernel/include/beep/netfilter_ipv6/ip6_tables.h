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
 * 	Format of an IP6 firewall descriptor
 *
 * 	src, dst, src_mask, dst_mask are always stored in network byte order.
 * 	flags are stored in host byte order (of course).
 * 	Port numbers are stored in HOST byte order.
 */
#ifndef _IP6_TABLES_H
#define _IP6_TABLES_H

#include <beep/if.h>
#include <beep/in6.h>
#include <beep/ipv6.h>
#include <beep/skbuff.h>

#include <beep/init.h>
#include <uapi/beep/netfilter_ipv6/ip6_tables.h>

extern void ip6t_init(void) __init;

extern void *ip6t_alloc_initial_table(const struct xt_table *);
extern struct xt_table *ip6t_register_table(struct net *net,
					    const struct xt_table *table,
					    const struct ip6t_replace *repl);
extern void ip6t_unregister_table(struct net *net, struct xt_table *table);
extern unsigned int ip6t_do_table(struct sk_buff *skb,
				  unsigned int hook,
				  const struct net_device *in,
				  const struct net_device *out,
				  struct xt_table *table);

/* Check for an extension */
static inline int
ip6t_ext_hdr(u8 nexthdr)
{	return (nexthdr == IPPROTO_HOPOPTS) ||
	       (nexthdr == IPPROTO_ROUTING) ||
	       (nexthdr == IPPROTO_FRAGMENT) ||
	       (nexthdr == IPPROTO_ESP) ||
	       (nexthdr == IPPROTO_AH) ||
	       (nexthdr == IPPROTO_NONE) ||
	       (nexthdr == IPPROTO_DSTOPTS);
}

#ifdef CONFIG_COMPAT
#include <net/compat.h>

struct compat_ip6t_entry {
	struct ip6t_ip6 ipv6;
	compat_uint_t nfcache;
	__u16 target_offset;
	__u16 next_offset;
	compat_uint_t comefrom;
	struct compat_xt_counters counters;
	unsigned char elems[0];
};

static inline struct xt_entry_target *
compat_ip6t_get_target(struct compat_ip6t_entry *e)
{
	return (void *)e + e->target_offset;
}

#endif /* CONFIG_COMPAT */
#endif /* _IP6_TABLES_H */
