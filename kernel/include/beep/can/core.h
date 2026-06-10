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
#ifndef CAN_CORE_H
#define CAN_CORE_H

#include <beep/can.h>
#include <beep/skbuff.h>
#include <beep/netdevice.h>

#define CAN_VERSION "20120528"

/* increment this number each time you change some user-space interface */
#define CAN_ABI_VERSION "9"

#define CAN_VERSION_STRING "rev " CAN_VERSION " abi " CAN_ABI_VERSION

#define DNAME(dev) ((dev) ? (dev)->name : "any")

/**
 * struct can_proto - CAN protocol structure
 * @type:       type argument in socket() syscall, e.g. SOCK_DGRAM.
 * @protocol:   protocol number in socket() syscall.
 * @ops:        pointer to struct proto_ops for sock->ops.
 * @prot:       pointer to struct proto structure.
 */
struct can_proto {
	int type;
	int protocol;
	const struct proto_ops *ops;
	struct proto *prot;
};

/* function prototypes for the CAN networklayer core (af_can.c) */

extern int  can_proto_register(const struct can_proto *cp);
extern void can_proto_unregister(const struct can_proto *cp);

extern int  can_rx_register(struct net_device *dev, canid_t can_id,
			    canid_t mask,
			    void (*func)(struct sk_buff *, void *),
			    void *data, char *ident);

extern void can_rx_unregister(struct net_device *dev, canid_t can_id,
			      canid_t mask,
			      void (*func)(struct sk_buff *, void *),
			      void *data);

extern int can_send(struct sk_buff *skb, int loop);
extern int can_ioctl(struct socket *sock, unsigned int cmd, unsigned long arg);

#endif /* CAN_CORE_H */
