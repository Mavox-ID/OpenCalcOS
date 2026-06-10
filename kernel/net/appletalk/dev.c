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
#include <beep/errno.h>
#include <beep/module.h>
#include <beep/netdevice.h>
#include <beep/if_arp.h>
#include <beep/if_ltalk.h>

static void ltalk_setup(struct net_device *dev)
{
	/* Fill in the fields of the device structure with localtalk-generic values. */

	dev->type		= ARPHRD_LOCALTLK;
	dev->hard_header_len 	= LTALK_HLEN;
	dev->mtu		= LTALK_MTU;
	dev->addr_len		= LTALK_ALEN;
	dev->tx_queue_len	= 10;

	dev->broadcast[0]	= 0xFF;

	dev->flags		= IFF_BROADCAST|IFF_MULTICAST|IFF_NOARP;
}

/**
 * alloc_ltalkdev - Allocates and sets up an localtalk device
 * @sizeof_priv: Size of additional driver-private structure to be allocated
 *	for this localtalk device
 *
 * Fill in the fields of the device structure with localtalk-generic
 * values. Basically does everything except registering the device.
 *
 * Constructs a new net device, complete with a private data area of
 * size @sizeof_priv.  A 32-byte (not bit) alignment is enforced for
 * this private data area.
 */

struct net_device *alloc_ltalkdev(int sizeof_priv)
{
	return alloc_netdev(sizeof_priv, "lt%d", ltalk_setup);
}
EXPORT_SYMBOL(alloc_ltalkdev);
