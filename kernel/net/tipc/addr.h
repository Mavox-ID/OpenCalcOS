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
#ifndef _TIPC_ADDR_H
#define _TIPC_ADDR_H

#define TIPC_ZONE_MASK		0xff000000u
#define TIPC_CLUSTER_MASK	0xfffff000u

static inline u32 tipc_zone_mask(u32 addr)
{
	return addr & TIPC_ZONE_MASK;
}

static inline u32 tipc_cluster_mask(u32 addr)
{
	return addr & TIPC_CLUSTER_MASK;
}

static inline int in_own_cluster_exact(u32 addr)
{
	return !((addr ^ tipc_own_addr) >> 12);
}

/**
 * in_own_node - test for node inclusion; <0.0.0> always matches
 */
static inline int in_own_node(u32 addr)
{
	return (addr == tipc_own_addr) || !addr;
}

/**
 * in_own_cluster - test for cluster inclusion; <0.0.0> always matches
 */
static inline int in_own_cluster(u32 addr)
{
	return in_own_cluster_exact(addr) || !addr;
}

/**
 * addr_domain - convert 2-bit scope value to equivalent message lookup domain
 *
 * Needed when address of a named message must be looked up a second time
 * after a network hop.
 */
static inline u32 addr_domain(u32 sc)
{
	if (likely(sc == TIPC_NODE_SCOPE))
		return tipc_own_addr;
	if (sc == TIPC_CLUSTER_SCOPE)
		return tipc_cluster_mask(tipc_own_addr);
	return tipc_zone_mask(tipc_own_addr);
}

int tipc_addr_domain_valid(u32);
int tipc_addr_node_valid(u32 addr);
int tipc_in_scope(u32 domain, u32 addr);
int tipc_addr_scope(u32 domain);
char *tipc_addr_string_fill(char *string, u32 addr);
#endif
