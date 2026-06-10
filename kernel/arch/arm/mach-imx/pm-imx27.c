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
#include <beep/suspend.h>
#include <beep/io.h>

#include "hardware.h"

static int mx27_suspend_enter(suspend_state_t state)
{
	u32 cscr;
	switch (state) {
	case PM_SUSPEND_MEM:
		/* Clear MPEN and SPEN to disable MPLL/SPLL */
		cscr = __raw_readl(MX27_IO_ADDRESS(MX27_CCM_BASE_ADDR));
		cscr &= 0xFFFFFFFC;
		__raw_writel(cscr, MX27_IO_ADDRESS(MX27_CCM_BASE_ADDR));
		/* Executes WFI */
		cpu_do_idle();
		break;

	default:
		return -EINVAL;
	}
	return 0;
}

static const struct platform_suspend_ops mx27_suspend_ops = {
	.enter = mx27_suspend_enter,
	.valid = suspend_valid_only_mem,
};

static int __init mx27_pm_init(void)
{
	if (!cpu_is_mx27())
		return 0;

	suspend_set_ops(&mx27_suspend_ops);
	return 0;
}

device_initcall(mx27_pm_init);
