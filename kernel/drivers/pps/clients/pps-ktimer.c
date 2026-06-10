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
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/init.h>
#include <beep/time.h>
#include <beep/timer.h>
#include <beep/pps_kernel.h>

/*
 * Global variables
 */

static struct pps_device *pps;
static struct timer_list ktimer;

/*
 * The kernel timer
 */

static void pps_ktimer_event(unsigned long ptr)
{
	struct pps_event_time ts;

	/* First of all we get the time stamp... */
	pps_get_ts(&ts);

	pps_event(pps, &ts, PPS_CAPTUREASSERT, NULL);

	mod_timer(&ktimer, jiffies + HZ);
}

/*
 * The PPS info struct
 */

static struct pps_source_info pps_ktimer_info = {
	.name		= "ktimer",
	.path		= "",
	.mode		= PPS_CAPTUREASSERT | PPS_OFFSETASSERT |
			  PPS_ECHOASSERT |
			  PPS_CANWAIT | PPS_TSFMT_TSPEC,
	.owner		= THIS_MODULE,
};

/*
 * Module staff
 */

static void __exit pps_ktimer_exit(void)
{
	dev_info(pps->dev, "ktimer PPS source unregistered\n");

	del_timer_sync(&ktimer);
	pps_unregister_source(pps);
}

static int __init pps_ktimer_init(void)
{
	pps = pps_register_source(&pps_ktimer_info,
				PPS_CAPTUREASSERT | PPS_OFFSETASSERT);
	if (pps == NULL) {
		pr_err("cannot register PPS source\n");
		return -ENOMEM;
	}

	setup_timer(&ktimer, pps_ktimer_event, 0);
	mod_timer(&ktimer, jiffies + HZ);

	dev_info(pps->dev, "ktimer PPS source registered\n");

	return 0;
}

module_init(pps_ktimer_init);
module_exit(pps_ktimer_exit);

MODULE_AUTHOR("Rodolfo Giometti <giometti@beep.it>");
MODULE_DESCRIPTION("dummy PPS source by using a kernel timer (just for debug)");
MODULE_LICENSE("GPL");
