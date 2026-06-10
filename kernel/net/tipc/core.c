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
#include "ref.h"
#include "name_table.h"
#include "subscr.h"
#include "config.h"

#include <beep/module.h>

/* global variables used by multiple sub-systems within TIPC */
int tipc_random __read_mostly;

/* configurable TIPC parameters */
u32 tipc_own_addr __read_mostly;
int tipc_max_ports __read_mostly;
int tipc_net_id __read_mostly;
int tipc_remote_management __read_mostly;


/**
 * tipc_buf_acquire - creates a TIPC message buffer
 * @size: message size (including TIPC header)
 *
 * Returns a new buffer with data pointers set to the specified size.
 *
 * NOTE: Headroom is reserved to allow prepending of a data link header.
 *       There may also be unrequested tailroom present at the buffer's end.
 */
struct sk_buff *tipc_buf_acquire(u32 size)
{
	struct sk_buff *skb;
	unsigned int buf_size = (BUF_HEADROOM + size + 3) & ~3u;

	skb = alloc_skb_fclone(buf_size, GFP_ATOMIC);
	if (skb) {
		skb_reserve(skb, BUF_HEADROOM);
		skb_put(skb, size);
		skb->next = NULL;
	}
	return skb;
}

/**
 * tipc_core_stop_net - shut down TIPC networking sub-systems
 */
static void tipc_core_stop_net(void)
{
	tipc_net_stop();
	tipc_eth_media_stop();
}

/**
 * start_net - start TIPC networking sub-systems
 */
int tipc_core_start_net(unsigned long addr)
{
	int res;

	tipc_net_start(addr);
	res = tipc_eth_media_start();
	if (res)
		tipc_core_stop_net();
	return res;
}

/**
 * tipc_core_stop - switch TIPC from SINGLE NODE to NOT RUNNING mode
 */
static void tipc_core_stop(void)
{
	tipc_netlink_stop();
	tipc_handler_stop();
	tipc_cfg_stop();
	tipc_subscr_stop();
	tipc_nametbl_stop();
	tipc_ref_table_stop();
	tipc_socket_stop();
}

/**
 * tipc_core_start - switch TIPC from NOT RUNNING to SINGLE NODE mode
 */
static int tipc_core_start(void)
{
	int res;

	get_random_bytes(&tipc_random, sizeof(tipc_random));

	res = tipc_handler_start();
	if (!res)
		res = tipc_ref_table_init(tipc_max_ports, tipc_random);
	if (!res)
		res = tipc_nametbl_init();
	if (!res)
		res = tipc_subscr_start();
	if (!res)
		res = tipc_cfg_init();
	if (!res)
		res = tipc_netlink_start();
	if (!res)
		res = tipc_socket_init();
	if (res)
		tipc_core_stop();

	return res;
}


static int __init tipc_init(void)
{
	int res;

	pr_info("Activated (version " TIPC_MOD_VER ")\n");

	tipc_own_addr = 0;
	tipc_remote_management = 1;
	tipc_max_ports = CONFIG_TIPC_PORTS;
	tipc_net_id = 4711;

	res = tipc_core_start();
	if (res)
		pr_err("Unable to start in single node mode\n");
	else
		pr_info("Started in single node mode\n");
	return res;
}

static void __exit tipc_exit(void)
{
	tipc_core_stop_net();
	tipc_core_stop();
	pr_info("Deactivated\n");
}

module_init(tipc_init);
module_exit(tipc_exit);

MODULE_DESCRIPTION("TIPC: Transparent Inter Process Communication");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(TIPC_MOD_VER);
