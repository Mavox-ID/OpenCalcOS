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
#include "core.h"
#include "config.h"
#include <net/genetlink.h>

static int handle_cmd(struct sk_buff *skb, struct genl_info *info)
{
	struct sk_buff *rep_buf;
	struct nlmsghdr *rep_nlh;
	struct nlmsghdr *req_nlh = info->nlhdr;
	struct tipc_genlmsghdr *req_userhdr = info->userhdr;
	int hdr_space = NLMSG_SPACE(GENL_HDRLEN + TIPC_GENL_HDRLEN);
	u16 cmd;

	if ((req_userhdr->cmd & 0xC000) && (!capable(CAP_NET_ADMIN)))
		cmd = TIPC_CMD_NOT_NET_ADMIN;
	else
		cmd = req_userhdr->cmd;

	rep_buf = tipc_cfg_do_cmd(req_userhdr->dest, cmd,
			NLMSG_DATA(req_nlh) + GENL_HDRLEN + TIPC_GENL_HDRLEN,
			NLMSG_PAYLOAD(req_nlh, GENL_HDRLEN + TIPC_GENL_HDRLEN),
			hdr_space);

	if (rep_buf) {
		skb_push(rep_buf, hdr_space);
		rep_nlh = nlmsg_hdr(rep_buf);
		memcpy(rep_nlh, req_nlh, hdr_space);
		rep_nlh->nlmsg_len = rep_buf->len;
		genlmsg_unicast(&init_net, rep_buf, NETLINK_CB(skb).portid);
	}

	return 0;
}

static struct genl_family tipc_genl_family = {
	.id		= GENL_ID_GENERATE,
	.name		= TIPC_GENL_NAME,
	.version	= TIPC_GENL_VERSION,
	.hdrsize	= TIPC_GENL_HDRLEN,
	.maxattr	= 0,
};

static struct genl_ops tipc_genl_ops = {
	.cmd		= TIPC_GENL_CMD,
	.doit		= handle_cmd,
};

static int tipc_genl_family_registered;

int tipc_netlink_start(void)
{
	int res;

	res = genl_register_family_with_ops(&tipc_genl_family,
		&tipc_genl_ops, 1);
	if (res) {
		pr_err("Failed to register netlink interface\n");
		return res;
	}

	tipc_genl_family_registered = 1;
	return 0;
}

void tipc_netlink_stop(void)
{
	if (!tipc_genl_family_registered)
		return;

	genl_unregister_family(&tipc_genl_family);
	tipc_genl_family_registered = 0;
}
