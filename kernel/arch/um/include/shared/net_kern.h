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
#ifndef __UM_NET_KERN_H
#define __UM_NET_KERN_H

#include <beep/netdevice.h>
#include <beep/platform_device.h>
#include <beep/skbuff.h>
#include <beep/socket.h>
#include <beep/list.h>
#include <beep/workqueue.h>

struct uml_net {
	struct list_head list;
	struct net_device *dev;
	struct platform_device pdev;
	int index;
	unsigned char mac[ETH_ALEN];
};

struct uml_net_private {
	struct list_head list;
	spinlock_t lock;
	struct net_device *dev;
	struct timer_list tl;

	struct work_struct work;
	int fd;
	unsigned char mac[ETH_ALEN];
	int max_packet;
	unsigned short (*protocol)(struct sk_buff *);
	int (*open)(void *);
	void (*close)(int, void *);
	void (*remove)(void *);
	int (*read)(int, struct sk_buff *skb, struct uml_net_private *);
	int (*write)(int, struct sk_buff *skb, struct uml_net_private *);

	void (*add_address)(unsigned char *, unsigned char *, void *);
	void (*delete_address)(unsigned char *, unsigned char *, void *);
	char user[0];
};

struct net_kern_info {
	void (*init)(struct net_device *, void *);
	unsigned short (*protocol)(struct sk_buff *);
	int (*read)(int, struct sk_buff *skb, struct uml_net_private *);
	int (*write)(int, struct sk_buff *skb, struct uml_net_private *);
};

struct transport {
	struct list_head list;
	const char *name;
	int (* const setup)(char *, char **, void *);
	const struct net_user_info *user;
	const struct net_kern_info *kern;
	const int private_size;
	const int setup_size;
};

extern struct net_device *ether_init(int);
extern unsigned short ether_protocol(struct sk_buff *);
extern int tap_setup_common(char *str, char *type, char **dev_name,
			    char **mac_out, char **gate_addr);
extern void register_transport(struct transport *new);
extern unsigned short eth_protocol(struct sk_buff *skb);

#endif
