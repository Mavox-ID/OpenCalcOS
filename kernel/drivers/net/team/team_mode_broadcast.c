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
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/module.h>
#include <beep/init.h>
#include <beep/errno.h>
#include <beep/netdevice.h>
#include <beep/if_team.h>

static bool bc_transmit(struct team *team, struct sk_buff *skb)
{
	struct team_port *cur;
	struct team_port *last = NULL;
	struct sk_buff *skb2;
	bool ret;
	bool sum_ret = false;

	list_for_each_entry_rcu(cur, &team->port_list, list) {
		if (team_port_txable(cur)) {
			if (last) {
				skb2 = skb_clone(skb, GFP_ATOMIC);
				if (skb2) {
					ret = !team_dev_queue_xmit(team, last,
								   skb2);
					if (!sum_ret)
						sum_ret = ret;
				}
			}
			last = cur;
		}
	}
	if (last) {
		ret = !team_dev_queue_xmit(team, last, skb);
		if (!sum_ret)
			sum_ret = ret;
	}
	return sum_ret;
}

static int bc_port_enter(struct team *team, struct team_port *port)
{
	return team_port_set_team_dev_addr(port);
}

static void bc_port_change_dev_addr(struct team *team, struct team_port *port)
{
	team_port_set_team_dev_addr(port);
}

static const struct team_mode_ops bc_mode_ops = {
	.transmit		= bc_transmit,
	.port_enter		= bc_port_enter,
	.port_change_dev_addr	= bc_port_change_dev_addr,
};

static const struct team_mode bc_mode = {
	.kind		= "broadcast",
	.owner		= THIS_MODULE,
	.ops		= &bc_mode_ops,
};

static int __init bc_init_module(void)
{
	return team_mode_register(&bc_mode);
}

static void __exit bc_cleanup_module(void)
{
	team_mode_unregister(&bc_mode);
}

module_init(bc_init_module);
module_exit(bc_cleanup_module);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jiri Pirko <jpirko@redhat.com>");
MODULE_DESCRIPTION("Broadcast mode for team");
MODULE_ALIAS("team-mode-broadcast");
