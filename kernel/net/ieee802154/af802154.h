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
#ifndef AF802154_H
#define AF802154_H

struct sk_buff;
struct net_devce;
extern struct proto ieee802154_raw_prot;
extern struct proto ieee802154_dgram_prot;
void ieee802154_raw_deliver(struct net_device *dev, struct sk_buff *skb);
int ieee802154_dgram_deliver(struct net_device *dev, struct sk_buff *skb);
struct net_device *ieee802154_get_dev(struct net *net,
		struct ieee802154_addr *addr);

#endif
