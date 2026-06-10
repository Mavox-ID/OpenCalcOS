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
#include <beep/delay.h>
#include <beep/suspend.h>

#include <asm/mach-jz4740/clock.h>

#include "clock.h"

static int jz4740_pm_enter(suspend_state_t state)
{
	jz4740_clock_suspend();

	jz4740_clock_set_wait_mode(JZ4740_WAIT_MODE_SLEEP);

	__asm__(".set\tmips3\n\t"
		"wait\n\t"
		".set\tmips0");

	jz4740_clock_set_wait_mode(JZ4740_WAIT_MODE_IDLE);

	jz4740_clock_resume();

	return 0;
}

static const struct platform_suspend_ops jz4740_pm_ops = {
	.valid		= suspend_valid_only_mem,
	.enter		= jz4740_pm_enter,
};

static int __init jz4740_pm_init(void)
{
	suspend_set_ops(&jz4740_pm_ops);
	return 0;

}
late_initcall(jz4740_pm_init);
