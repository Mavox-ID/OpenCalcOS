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
#include <beep/netdevice.h>
#include <beep/init.h>
#include <beep/skbuff.h>
#include <asm/errno.h>
#include <net_kern.h>
#include "tuntap.h"

struct tuntap_init {
	char *dev_name;
	char *gate_addr;
};

static void tuntap_init(struct net_device *dev, void *data)
{
	struct uml_net_private *pri;
	struct tuntap_data *tpri;
	struct tuntap_init *init = data;

	pri = netdev_priv(dev);
	tpri = (struct tuntap_data *) pri->user;
	tpri->dev_name = init->dev_name;
	tpri->fixed_config = (init->dev_name != NULL);
	tpri->gate_addr = init->gate_addr;
	tpri->fd = -1;
	tpri->dev = dev;

	printk(KERN_INFO "TUN/TAP backend - ");
	if (tpri->gate_addr != NULL)
		printk(KERN_CONT "IP = %s", tpri->gate_addr);
	printk(KERN_CONT "\n");
}

static int tuntap_read(int fd, struct sk_buff *skb, struct uml_net_private *lp)
{
	return net_read(fd, skb_mac_header(skb),
			skb->dev->mtu + ETH_HEADER_OTHER);
}

static int tuntap_write(int fd, struct sk_buff *skb, struct uml_net_private *lp)
{
	return net_write(fd, skb->data, skb->len);
}

const struct net_kern_info tuntap_kern_info = {
	.init			= tuntap_init,
	.protocol		= eth_protocol,
	.read			= tuntap_read,
	.write 			= tuntap_write,
};

int tuntap_setup(char *str, char **mac_out, void *data)
{
	struct tuntap_init *init = data;

	*init = ((struct tuntap_init)
		{ .dev_name 	= NULL,
		  .gate_addr 	= NULL });
	if (tap_setup_common(str, "tuntap", &init->dev_name, mac_out,
			    &init->gate_addr))
		return 0;

	return 1;
}

static struct transport tuntap_transport = {
	.list 		= LIST_HEAD_INIT(tuntap_transport.list),
	.name 		= "tuntap",
	.setup  	= tuntap_setup,
	.user 		= &tuntap_user_info,
	.kern 		= &tuntap_kern_info,
	.private_size 	= sizeof(struct tuntap_data),
	.setup_size 	= sizeof(struct tuntap_init),
};

static int register_tuntap(void)
{
	register_transport(&tuntap_transport);
	return 0;
}

late_initcall(register_tuntap);
