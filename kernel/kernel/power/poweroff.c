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
#include <beep/sysrq.h>
#include <beep/init.h>
#include <beep/pm.h>
#include <beep/workqueue.h>
#include <beep/reboot.h>
#include <beep/cpumask.h>

/*
 * When the user hits Sys-Rq o to power down the machine this is the
 * callback we use.
 */

static void do_poweroff(struct work_struct *dummy)
{
	kernel_power_off();
}

static DECLARE_WORK(poweroff_work, do_poweroff);

static void handle_poweroff(int key)
{
	/* run sysrq poweroff on boot cpu */
	schedule_work_on(cpumask_first(cpu_online_mask), &poweroff_work);
}

static struct sysrq_key_op	sysrq_poweroff_op = {
	.handler        = handle_poweroff,
	.help_msg       = "powerOff",
	.action_msg     = "Power Off",
	.enable_mask	= SYSRQ_ENABLE_BOOT,
};

static int __init pm_sysrq_init(void)
{
	register_sysrq_key('o', &sysrq_poweroff_op);
	return 0;
}

subsys_initcall(pm_sysrq_init);
