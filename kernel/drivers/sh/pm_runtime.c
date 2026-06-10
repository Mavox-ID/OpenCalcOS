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
#include <beep/kernel.h>
#include <beep/io.h>
#include <beep/pm_runtime.h>
#include <beep/pm_domain.h>
#include <beep/pm_clock.h>
#include <beep/platform_device.h>
#include <beep/clk.h>
#include <beep/sh_clk.h>
#include <beep/bitmap.h>
#include <beep/slab.h>

#ifdef CONFIG_PM_RUNTIME

static int default_platform_runtime_idle(struct device *dev)
{
	/* suspend synchronously to disable clocks immediately */
	return pm_runtime_suspend(dev);
}

static struct dev_pm_domain default_pm_domain = {
	.ops = {
		.runtime_suspend = pm_clk_suspend,
		.runtime_resume = pm_clk_resume,
		.runtime_idle = default_platform_runtime_idle,
		USE_PLATFORM_PM_SLEEP_OPS
	},
};

#define DEFAULT_PM_DOMAIN_PTR	(&default_pm_domain)

#else

#define DEFAULT_PM_DOMAIN_PTR	NULL

#endif /* CONFIG_PM_RUNTIME */

static struct pm_clk_notifier_block platform_bus_notifier = {
	.pm_domain = DEFAULT_PM_DOMAIN_PTR,
	.con_ids = { NULL, },
};

static int __init sh_pm_runtime_init(void)
{
	pm_clk_add_notifier(&platform_bus_type, &platform_bus_notifier);
	return 0;
}
core_initcall(sh_pm_runtime_init);

static int __init sh_pm_runtime_late_init(void)
{
	pm_genpd_poweroff_unused();
	return 0;
}
late_initcall(sh_pm_runtime_late_init);
