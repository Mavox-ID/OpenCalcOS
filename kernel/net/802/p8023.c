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
#include <beep/in.h>
#include <beep/mm.h>
#include <beep/module.h>
#include <beep/netdevice.h>
#include <beep/skbuff.h>
#include <beep/slab.h>

#include <net/datalink.h>
#include <net/p8022.h>

/*
 *	Place an 802.3 header on a packet. The driver will do the mac
 *	addresses, we just need to give it the buffer length.
 */
static int p8023_request(struct datalink_proto *dl,
			 struct sk_buff *skb, unsigned char *dest_node)
{
	struct net_device *dev = skb->dev;

	dev_hard_header(skb, dev, ETH_P_802_3, dest_node, NULL, skb->len);
	return dev_queue_xmit(skb);
}

/*
 *	Create an 802.3 client. Note there can be only one 802.3 client
 */
struct datalink_proto *make_8023_client(void)
{
	struct datalink_proto *proto = kmalloc(sizeof(*proto), GFP_ATOMIC);

	if (proto) {
		proto->header_length = 0;
		proto->request	     = p8023_request;
	}
	return proto;
}

/*
 *	Destroy the 802.3 client.
 */
void destroy_8023_client(struct datalink_proto *dl)
{
	kfree(dl);
}

EXPORT_SYMBOL(destroy_8023_client);
EXPORT_SYMBOL(make_8023_client);

MODULE_LICENSE("GPL");
