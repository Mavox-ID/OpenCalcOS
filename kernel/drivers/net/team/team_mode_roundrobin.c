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

struct rr_priv {
	unsigned int sent_packets;
};

static struct rr_priv *rr_priv(struct team *team)
{
	return (struct rr_priv *) &team->mode_priv;
}

static struct team_port *__get_first_port_up(struct team *team,
					     struct team_port *port)
{
	struct team_port *cur;

	if (team_port_txable(port))
		return port;
	cur = port;
	list_for_each_entry_continue_rcu(cur, &team->port_list, list)
		if (team_port_txable(port))
			return cur;
	list_for_each_entry_rcu(cur, &team->port_list, list) {
		if (cur == port)
			break;
		if (team_port_txable(port))
			return cur;
	}
	return NULL;
}

static bool rr_transmit(struct team *team, struct sk_buff *skb)
{
	struct team_port *port;
	int port_index;

	port_index = rr_priv(team)->sent_packets++ % team->en_port_count;
	port = team_get_port_by_index_rcu(team, port_index);
	port = __get_first_port_up(team, port);
	if (unlikely(!port))
		goto drop;
	if (team_dev_queue_xmit(team, port, skb))
		return false;
	return true;

drop:
	dev_kfree_skb_any(skb);
	return false;
}

static int rr_port_enter(struct team *team, struct team_port *port)
{
	return team_port_set_team_dev_addr(port);
}

static void rr_port_change_dev_addr(struct team *team, struct team_port *port)
{
	team_port_set_team_dev_addr(port);
}

static const struct team_mode_ops rr_mode_ops = {
	.transmit		= rr_transmit,
	.port_enter		= rr_port_enter,
	.port_change_dev_addr	= rr_port_change_dev_addr,
};

static const struct team_mode rr_mode = {
	.kind		= "roundrobin",
	.owner		= THIS_MODULE,
	.priv_size	= sizeof(struct rr_priv),
	.ops		= &rr_mode_ops,
};

static int __init rr_init_module(void)
{
	return team_mode_register(&rr_mode);
}

static void __exit rr_cleanup_module(void)
{
	team_mode_unregister(&rr_mode);
}

module_init(rr_init_module);
module_exit(rr_cleanup_module);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jiri Pirko <jpirko@redhat.com>");
MODULE_DESCRIPTION("Round-robin mode for team");
MODULE_ALIAS("team-mode-roundrobin");
