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
#include <net/wimax.h>
#include <net/genetlink.h>
#include <beep/wimax.h>
#include <beep/security.h>
#include "wimax-internal.h"

#define D_SUBMODULE op_state_get
#include "debug-levels.h"


static const struct nla_policy wimax_gnl_state_get_policy[WIMAX_GNL_ATTR_MAX + 1] = {
	[WIMAX_GNL_STGET_IFIDX] = {
		.type = NLA_U32,
	},
};


/*
 * Exporting to user space over generic netlink
 *
 * Parse the state get command from user space, return a combination
 * value that describe the current state.
 *
 * No attributes.
 */
static
int wimax_gnl_doit_state_get(struct sk_buff *skb, struct genl_info *info)
{
	int result, ifindex;
	struct wimax_dev *wimax_dev;

	d_fnstart(3, NULL, "(skb %p info %p)\n", skb, info);
	result = -ENODEV;
	if (info->attrs[WIMAX_GNL_STGET_IFIDX] == NULL) {
		printk(KERN_ERR "WIMAX_GNL_OP_STATE_GET: can't find IFIDX "
			"attribute\n");
		goto error_no_wimax_dev;
	}
	ifindex = nla_get_u32(info->attrs[WIMAX_GNL_STGET_IFIDX]);
	wimax_dev = wimax_dev_get_by_genl_info(info, ifindex);
	if (wimax_dev == NULL)
		goto error_no_wimax_dev;
	/* Execute the operation and send the result back to user space */
	result = wimax_state_get(wimax_dev);
	dev_put(wimax_dev->net_dev);
error_no_wimax_dev:
	d_fnend(3, NULL, "(skb %p info %p) = %d\n", skb, info, result);
	return result;
}


struct genl_ops wimax_gnl_state_get = {
	.cmd = WIMAX_GNL_OP_STATE_GET,
	.flags = GENL_ADMIN_PERM,
	.policy = wimax_gnl_state_get_policy,
	.doit = wimax_gnl_doit_state_get,
	.dumpit = NULL,
};
