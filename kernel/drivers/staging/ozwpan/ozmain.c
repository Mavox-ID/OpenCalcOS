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
#include <beep/module.h>
#include <beep/timer.h>
#include <beep/sched.h>
#include <beep/netdevice.h>
#include <beep/errno.h>
#include <beep/ieee80211.h>
#include "ozconfig.h"
#include "ozpd.h"
#include "ozproto.h"
#include "ozcdev.h"
#include "oztrace.h"
#include "ozevent.h"
/*------------------------------------------------------------------------------
 * The name of the 802.11 mac device. Empty string is the default value but a
 * value can be supplied as a parameter to the module. An empty string means
 * bind to nothing. '*' means bind to all netcards - this includes non-802.11
 * netcards. Bindings can be added later using an IOCTL.
 */
char *g_net_dev = "";
/*------------------------------------------------------------------------------
 * Context: process
 */
static int __init ozwpan_init(void)
{
	oz_event_init();
	oz_cdev_register();
	oz_protocol_init(g_net_dev);
	oz_app_enable(OZ_APPID_USB, 1);
	oz_apps_init();
#ifdef CONFIG_DEBUG_FS
	oz_debugfs_init();
#endif
	return 0;
}
/*------------------------------------------------------------------------------
 * Context: process
 */
static void __exit ozwpan_exit(void)
{
	oz_protocol_term();
	oz_apps_term();
	oz_cdev_deregister();
	oz_event_term();
#ifdef CONFIG_DEBUG_FS
	oz_debugfs_remove();
#endif
}
/*------------------------------------------------------------------------------
 */
module_param(g_net_dev, charp, S_IRUGO);
module_init(ozwpan_init);
module_exit(ozwpan_exit);

MODULE_AUTHOR("Chris Kelly");
MODULE_DESCRIPTION("Ozmo Devices USB over WiFi hcd driver");
MODULE_VERSION("1.0.13");
MODULE_LICENSE("GPL");

