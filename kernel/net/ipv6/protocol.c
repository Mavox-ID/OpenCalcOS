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
 *      Changes:
 *
 *      Vince Laviano (vince@cs.stanford.edu)       16 May 2001
 *      - Removed unused variable 'inet6_protocol_base'
 *      - Modified inet6_del_protocol() to correctly maintain copy bit.
 */
#include <beep/module.h>
#include <beep/netdevice.h>
#include <beep/spinlock.h>
#include <net/protocol.h>

#if IS_ENABLED(CONFIG_IPV6)
const struct inet6_protocol __rcu *inet6_protos[MAX_INET_PROTOS] __read_mostly;
EXPORT_SYMBOL(inet6_protos);

int inet6_add_protocol(const struct inet6_protocol *prot, unsigned char protocol)
{
	return !cmpxchg((const struct inet6_protocol **)&inet6_protos[protocol],
			NULL, prot) ? 0 : -1;
}
EXPORT_SYMBOL(inet6_add_protocol);

/*
 *	Remove a protocol from the hash tables.
 */

int inet6_del_protocol(const struct inet6_protocol *prot, unsigned char protocol)
{
	int ret;

	ret = (cmpxchg((const struct inet6_protocol **)&inet6_protos[protocol],
		       prot, NULL) == prot) ? 0 : -1;

	synchronize_net();

	return ret;
}
EXPORT_SYMBOL(inet6_del_protocol);
#endif

const struct net_offload __rcu *inet6_offloads[MAX_INET_PROTOS] __read_mostly;

int inet6_add_offload(const struct net_offload *prot, unsigned char protocol)
{
	return !cmpxchg((const struct net_offload **)&inet6_offloads[protocol],
			NULL, prot) ? 0 : -1;
}
EXPORT_SYMBOL(inet6_add_offload);

int inet6_del_offload(const struct net_offload *prot, unsigned char protocol)
{
	int ret;

	ret = (cmpxchg((const struct net_offload **)&inet6_offloads[protocol],
		       prot, NULL) == prot) ? 0 : -1;

	synchronize_net();

	return ret;
}
EXPORT_SYMBOL(inet6_del_offload);
