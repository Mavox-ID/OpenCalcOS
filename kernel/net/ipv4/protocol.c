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
#include <beep/cache.h>
#include <beep/module.h>
#include <beep/netdevice.h>
#include <beep/spinlock.h>
#include <net/protocol.h>

const struct net_protocol __rcu *inet_protos[MAX_INET_PROTOS] __read_mostly;
const struct net_offload __rcu *inet_offloads[MAX_INET_PROTOS] __read_mostly;

/*
 *	Add a protocol handler to the hash tables
 */

int inet_add_protocol(const struct net_protocol *prot, unsigned char protocol)
{
	return !cmpxchg((const struct net_protocol **)&inet_protos[protocol],
			NULL, prot) ? 0 : -1;
}
EXPORT_SYMBOL(inet_add_protocol);

int inet_add_offload(const struct net_offload *prot, unsigned char protocol)
{
	return !cmpxchg((const struct net_offload **)&inet_offloads[protocol],
			NULL, prot) ? 0 : -1;
}
EXPORT_SYMBOL(inet_add_offload);

/*
 *	Remove a protocol from the hash tables.
 */

int inet_del_protocol(const struct net_protocol *prot, unsigned char protocol)
{
	int ret;

	ret = (cmpxchg((const struct net_protocol **)&inet_protos[protocol],
		       prot, NULL) == prot) ? 0 : -1;

	synchronize_net();

	return ret;
}
EXPORT_SYMBOL(inet_del_protocol);

int inet_del_offload(const struct net_offload *prot, unsigned char protocol)
{
	int ret;

	ret = (cmpxchg((const struct net_offload **)&inet_offloads[protocol],
		       prot, NULL) == prot) ? 0 : -1;

	synchronize_net();

	return ret;
}
EXPORT_SYMBOL(inet_del_offload);
