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
#include <beep/module.h>
#include <beep/netdevice.h>
#include <beep/skbuff.h>
#include <beep/slab.h>
#include <net/datalink.h>
#include <beep/mm.h>
#include <beep/in.h>
#include <beep/init.h>
#include <net/llc.h>
#include <net/p8022.h>

static int p8022_request(struct datalink_proto *dl, struct sk_buff *skb,
			 unsigned char *dest)
{
	llc_build_and_send_ui_pkt(dl->sap, skb, dest, dl->sap->laddr.lsap);
	return 0;
}

struct datalink_proto *register_8022_client(unsigned char type,
					    int (*func)(struct sk_buff *skb,
							struct net_device *dev,
							struct packet_type *pt,
							struct net_device *orig_dev))
{
	struct datalink_proto *proto;

	proto = kmalloc(sizeof(*proto), GFP_ATOMIC);
	if (proto) {
		proto->type[0]		= type;
		proto->header_length	= 3;
		proto->request		= p8022_request;
		proto->sap = llc_sap_open(type, func);
		if (!proto->sap) {
			kfree(proto);
			proto = NULL;
		}
	}
	return proto;
}

void unregister_8022_client(struct datalink_proto *proto)
{
	llc_sap_put(proto->sap);
	kfree(proto);
}

EXPORT_SYMBOL(register_8022_client);
EXPORT_SYMBOL(unregister_8022_client);

MODULE_LICENSE("GPL");
