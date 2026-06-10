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
#include "core.h"
#include "addr.h"

/**
 * tipc_addr_domain_valid - validates a network domain address
 *
 * Accepts <Z.C.N>, <Z.C.0>, <Z.0.0>, and <0.0.0>,
 * where Z, C, and N are non-zero.
 *
 * Returns 1 if domain address is valid, otherwise 0
 */
int tipc_addr_domain_valid(u32 addr)
{
	u32 n = tipc_node(addr);
	u32 c = tipc_cluster(addr);
	u32 z = tipc_zone(addr);

	if (n && (!z || !c))
		return 0;
	if (c && !z)
		return 0;
	return 1;
}

/**
 * tipc_addr_node_valid - validates a proposed network address for this node
 *
 * Accepts <Z.C.N>, where Z, C, and N are non-zero.
 *
 * Returns 1 if address can be used, otherwise 0
 */
int tipc_addr_node_valid(u32 addr)
{
	return tipc_addr_domain_valid(addr) && tipc_node(addr);
}

int tipc_in_scope(u32 domain, u32 addr)
{
	if (!domain || (domain == addr))
		return 1;
	if (domain == tipc_cluster_mask(addr)) /* domain <Z.C.0> */
		return 1;
	if (domain == tipc_zone_mask(addr)) /* domain <Z.0.0> */
		return 1;
	return 0;
}

/**
 * tipc_addr_scope - convert message lookup domain to a 2-bit scope value
 */
int tipc_addr_scope(u32 domain)
{
	if (likely(!domain))
		return TIPC_ZONE_SCOPE;
	if (tipc_node(domain))
		return TIPC_NODE_SCOPE;
	if (tipc_cluster(domain))
		return TIPC_CLUSTER_SCOPE;
	return TIPC_ZONE_SCOPE;
}

char *tipc_addr_string_fill(char *string, u32 addr)
{
	snprintf(string, 16, "<%u.%u.%u>",
		 tipc_zone(addr), tipc_cluster(addr), tipc_node(addr));
	return string;
}
