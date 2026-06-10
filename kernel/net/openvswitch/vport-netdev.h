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
#ifndef VPORT_NETDEV_H
#define VPORT_NETDEV_H 1

#include <beep/netdevice.h>
#include <beep/rcupdate.h>

#include "vport.h"

struct vport *ovs_netdev_get_vport(struct net_device *dev);

struct netdev_vport {
	struct rcu_head rcu;

	struct net_device *dev;
};

static inline struct netdev_vport *
netdev_vport_priv(const struct vport *vport)
{
	return vport_priv(vport);
}

const char *ovs_netdev_get_name(const struct vport *);
const char *ovs_netdev_get_config(const struct vport *);
int ovs_netdev_get_ifindex(const struct vport *);

#endif /* vport_netdev.h */
