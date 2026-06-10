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
#if !defined(NETLINK_H_20081202)
#define NETLINK_H_20081202
#include <beep/netdevice.h>
#include <net/sock.h>

struct sock *netlink_init(int unit,
	void (*cb)(struct net_device *dev, u16 type, void *msg, int len));
void netlink_exit(struct sock *sock);
int netlink_send(struct sock *sock, int group, u16 type, void *msg, int len);

#endif
