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
#include <beep/pm.h>
#include <beep/sched.h>
#include <beep/interrupt.h>
#include <beep/sysctl.h>
#include <beep/errno.h>
#include <beep/delay.h>
#include <asm/uaccess.h>

#include <asm/mb86943a.h>

#include "local.h"

static unsigned long imask;
/*
 * Setup interrupt masks, etc to enable wakeup by power switch
 */
static void mb93093_power_switch_setup(void)
{
	/* mask all but FPGA interrupt sources. */
	imask = *(volatile unsigned long *)0xfeff9820;
	*(volatile unsigned long *)0xfeff9820 = ~(1 << (IRQ_XIRQ2_LEVEL + 16)) & 0xfffe0000;
}

/*
 * Cleanup interrupt masks, etc after wakeup by power switch
 */
static void mb93093_power_switch_cleanup(void)
{
	*(volatile unsigned long *)0xfeff9820 = imask;
}

/*
 * Return non-zero if wakeup irq was caused by power switch
 */
static int mb93093_power_switch_check(void)
{
	return 1;
}

/*
 * Initialize power interface
 */
static int __init mb93093_pm_init(void)
{
	__power_switch_wake_setup = mb93093_power_switch_setup;
	__power_switch_wake_check = mb93093_power_switch_check;
	__power_switch_wake_cleanup = mb93093_power_switch_cleanup;
	return 0;
}

__initcall(mb93093_pm_init);

