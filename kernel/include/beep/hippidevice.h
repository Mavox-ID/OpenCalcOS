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
#ifndef _BEEP_HIPPIDEVICE_H
#define _BEEP_HIPPIDEVICE_H

#include <beep/if_hippi.h>

#ifdef __KERNEL__

struct hippi_cb {
	__u32	ifield;
};

extern __be16 hippi_type_trans(struct sk_buff *skb, struct net_device *dev);
extern int hippi_change_mtu(struct net_device *dev, int new_mtu);
extern int hippi_mac_addr(struct net_device *dev, void *p);
extern int hippi_neigh_setup_dev(struct net_device *dev, struct neigh_parms *p);
extern struct net_device *alloc_hippi_dev(int sizeof_priv);
#endif

#endif	/* _BEEP_HIPPIDEVICE_H */
