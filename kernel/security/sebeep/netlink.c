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
#include <beep/init.h>
#include <beep/types.h>
#include <beep/slab.h>
#include <beep/stddef.h>
#include <beep/kernel.h>
#include <beep/export.h>
#include <beep/skbuff.h>
#include <beep/netlink.h>
#include <beep/sebeep_netlink.h>
#include <net/net_namespace.h>
#include <net/netlink.h>

#include "security.h"

static struct sock *selnl;

static int selnl_msglen(int msgtype)
{
	int ret = 0;

	switch (msgtype) {
	case SELNL_MSG_SETENFORCE:
		ret = sizeof(struct selnl_msg_setenforce);
		break;

	case SELNL_MSG_POLICYLOAD:
		ret = sizeof(struct selnl_msg_policyload);
		break;

	default:
		BUG();
	}
	return ret;
}

static void selnl_add_payload(struct nlmsghdr *nlh, int len, int msgtype, void *data)
{
	switch (msgtype) {
	case SELNL_MSG_SETENFORCE: {
		struct selnl_msg_setenforce *msg = nlmsg_data(nlh);

		memset(msg, 0, len);
		msg->val = *((int *)data);
		break;
	}

	case SELNL_MSG_POLICYLOAD: {
		struct selnl_msg_policyload *msg = nlmsg_data(nlh);

		memset(msg, 0, len);
		msg->seqno = *((u32 *)data);
		break;
	}

	default:
		BUG();
	}
}

static void selnl_notify(int msgtype, void *data)
{
	int len;
	sk_buff_data_t tmp;
	struct sk_buff *skb;
	struct nlmsghdr *nlh;

	len = selnl_msglen(msgtype);

	skb = alloc_skb(NLMSG_SPACE(len), GFP_USER);
	if (!skb)
		goto oom;

	tmp = skb->tail;
	nlh = nlmsg_put(skb, 0, 0, msgtype, len, 0);
	if (!nlh)
		goto out_kfree_skb;
	selnl_add_payload(nlh, len, msgtype, data);
	nlh->nlmsg_len = skb->tail - tmp;
	NETLINK_CB(skb).dst_group = SELNLGRP_AVC;
	netlink_broadcast(selnl, skb, 0, SELNLGRP_AVC, GFP_USER);
out:
	return;

out_kfree_skb:
	kfree_skb(skb);
oom:
	printk(KERN_ERR "SEBeep:  OOM in %s\n", __func__);
	goto out;
}

void selnl_notify_setenforce(int val)
{
	selnl_notify(SELNL_MSG_SETENFORCE, &val);
}

void selnl_notify_policyload(u32 seqno)
{
	selnl_notify(SELNL_MSG_POLICYLOAD, &seqno);
}

static int __init selnl_init(void)
{
	struct netlink_kernel_cfg cfg = {
		.groups	= SELNLGRP_MAX,
		.flags	= NL_CFG_F_NONROOT_RECV,
	};

	selnl = netlink_kernel_create(&init_net, NETLINK_SEBEEP, &cfg);
	if (selnl == NULL)
		panic("SEBeep:  Cannot create netlink socket.");
	return 0;
}

__initcall(selnl_init);
