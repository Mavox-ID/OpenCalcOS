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
#include <beep/device.h>
#include <net/genetlink.h>
#include <beep/netdevice.h>
#include <beep/list.h>
#include <beep/wimax.h>
#include "wimax-internal.h"


#define D_SUBMODULE id_table
#include "debug-levels.h"


static DEFINE_SPINLOCK(wimax_id_table_lock);
static struct list_head wimax_id_table = LIST_HEAD_INIT(wimax_id_table);


/*
 * wimax_id_table_add - add a gennetlink familiy ID / wimax_dev mapping
 *
 * @wimax_dev: WiMAX device descriptor to associate to the Generic
 *     Netlink family ID.
 *
 * Look for an empty spot in the ID table; if none found, double the
 * table's size and get the first spot.
 */
void wimax_id_table_add(struct wimax_dev *wimax_dev)
{
	d_fnstart(3, NULL, "(wimax_dev %p)\n", wimax_dev);
	spin_lock(&wimax_id_table_lock);
	list_add(&wimax_dev->id_table_node, &wimax_id_table);
	spin_unlock(&wimax_id_table_lock);
	d_fnend(3, NULL, "(wimax_dev %p)\n", wimax_dev);
}


/*
 * wimax_get_netdev_by_info - lookup a wimax_dev from the gennetlink info
 *
 * The generic netlink family ID has been filled out in the
 * nlmsghdr->nlmsg_type field, so we pull it from there, look it up in
 * the mapping table and reference the wimax_dev.
 *
 * When done, the reference should be dropped with
 * 'dev_put(wimax_dev->net_dev)'.
 */
struct wimax_dev *wimax_dev_get_by_genl_info(
	struct genl_info *info, int ifindex)
{
	struct wimax_dev *wimax_dev = NULL;

	d_fnstart(3, NULL, "(info %p ifindex %d)\n", info, ifindex);
	spin_lock(&wimax_id_table_lock);
	list_for_each_entry(wimax_dev, &wimax_id_table, id_table_node) {
		if (wimax_dev->net_dev->ifindex == ifindex) {
			dev_hold(wimax_dev->net_dev);
			goto found;
		}
	}
	wimax_dev = NULL;
	d_printf(1, NULL, "wimax: no devices found with ifindex %d\n",
		 ifindex);
found:
	spin_unlock(&wimax_id_table_lock);
	d_fnend(3, NULL, "(info %p ifindex %d) = %p\n",
		info, ifindex, wimax_dev);
	return wimax_dev;
}


/*
 * wimax_id_table_rm - Remove a gennetlink familiy ID / wimax_dev mapping
 *
 * @id: family ID to remove from the table
 */
void wimax_id_table_rm(struct wimax_dev *wimax_dev)
{
	spin_lock(&wimax_id_table_lock);
	list_del_init(&wimax_dev->id_table_node);
	spin_unlock(&wimax_id_table_lock);
}


/*
 * Release the gennetlink family id / mapping table
 *
 * On debug, verify that the table is empty upon removal. We want the
 * code always compiled, to ensure it doesn't bit rot. It will be
 * compiled out if CONFIG_BUG is disabled.
 */
void wimax_id_table_release(void)
{
	struct wimax_dev *wimax_dev;

#ifndef CONFIG_BUG
	return;
#endif
	spin_lock(&wimax_id_table_lock);
	list_for_each_entry(wimax_dev, &wimax_id_table, id_table_node) {
		printk(KERN_ERR "BUG: %s wimax_dev %p ifindex %d not cleared\n",
		       __func__, wimax_dev, wimax_dev->net_dev->ifindex);
		WARN_ON(1);
	}
	spin_unlock(&wimax_id_table_lock);
}
