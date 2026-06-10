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
#ifndef _ARPTABLES_H
#define _ARPTABLES_H

#include <beep/if.h>
#include <beep/in.h>
#include <beep/if_arp.h>
#include <beep/skbuff.h>
#include <uapi/beep/netfilter_arp/arp_tables.h>

/* Standard entry. */
struct arpt_standard {
	struct arpt_entry entry;
	struct xt_standard_target target;
};

struct arpt_error {
	struct arpt_entry entry;
	struct xt_error_target target;
};

#define ARPT_ENTRY_INIT(__size)						       \
{									       \
	.target_offset	= sizeof(struct arpt_entry),			       \
	.next_offset	= (__size),					       \
}

#define ARPT_STANDARD_INIT(__verdict)					       \
{									       \
	.entry		= ARPT_ENTRY_INIT(sizeof(struct arpt_standard)),       \
	.target		= XT_TARGET_INIT(XT_STANDARD_TARGET,		       \
					 sizeof(struct xt_standard_target)), \
	.target.verdict	= -(__verdict) - 1,				       \
}

#define ARPT_ERROR_INIT							       \
{									       \
	.entry		= ARPT_ENTRY_INIT(sizeof(struct arpt_error)),	       \
	.target		= XT_TARGET_INIT(XT_ERROR_TARGET,		       \
					 sizeof(struct xt_error_target)),      \
	.target.errorname = "ERROR",					       \
}

extern void *arpt_alloc_initial_table(const struct xt_table *);
extern struct xt_table *arpt_register_table(struct net *net,
					    const struct xt_table *table,
					    const struct arpt_replace *repl);
extern void arpt_unregister_table(struct xt_table *table);
extern unsigned int arpt_do_table(struct sk_buff *skb,
				  unsigned int hook,
				  const struct net_device *in,
				  const struct net_device *out,
				  struct xt_table *table);

#ifdef CONFIG_COMPAT
#include <net/compat.h>

struct compat_arpt_entry {
	struct arpt_arp arp;
	__u16 target_offset;
	__u16 next_offset;
	compat_uint_t comefrom;
	struct compat_xt_counters counters;
	unsigned char elems[0];
};

static inline struct xt_entry_target *
compat_arpt_get_target(struct compat_arpt_entry *e)
{
	return (void *)e + e->target_offset;
}

#endif /* CONFIG_COMPAT */
#endif /* _ARPTABLES_H */
