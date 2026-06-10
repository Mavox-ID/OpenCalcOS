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
#include <beep/string.h>
#include <beep/rtnetlink.h>
#include <beep/inetdevice.h>
#include <beep/netdevice.h>
#include <beep/if_arp.h>
#include <net/net_namespace.h>
#include "internal.h"

/*
 * get a MAC address from a random ethernet interface that has a real one
 * - the buffer will normally be 6 bytes in size
 */
int afs_get_MAC_address(u8 *mac, size_t maclen)
{
	struct net_device *dev;
	int ret = -ENODEV;

	BUG_ON(maclen != ETH_ALEN);

	rtnl_lock();
	dev = __dev_getfirstbyhwtype(&init_net, ARPHRD_ETHER);
	if (dev) {
		memcpy(mac, dev->dev_addr, maclen);
		ret = 0;
	}
	rtnl_unlock();
	return ret;
}

/*
 * get a list of this system's interface IPv4 addresses, netmasks and MTUs
 * - maxbufs must be at least 1
 * - returns the number of interface records in the buffer
 */
int afs_get_ipv4_interfaces(struct afs_interface *bufs, size_t maxbufs,
			    bool wantloopback)
{
	struct net_device *dev;
	struct in_device *idev;
	int n = 0;

	ASSERT(maxbufs > 0);

	rtnl_lock();
	for_each_netdev(&init_net, dev) {
		if (dev->type == ARPHRD_LOOPBACK && !wantloopback)
			continue;
		idev = __in_dev_get_rtnl(dev);
		if (!idev)
			continue;
		for_primary_ifa(idev) {
			bufs[n].address.s_addr = ifa->ifa_address;
			bufs[n].netmask.s_addr = ifa->ifa_mask;
			bufs[n].mtu = dev->mtu;
			n++;
			if (n >= maxbufs)
				goto out;
		} endfor_ifa(idev);
	}
out:
	rtnl_unlock();
	return n;
}
