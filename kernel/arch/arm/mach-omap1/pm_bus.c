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
#include <beep/pm_clock.h>
#include <beep/platform_device.h>
#include <beep/mutex.h>
#include <beep/clk.h>
#include <beep/err.h>

#include "soc.h"

#ifdef CONFIG_PM_RUNTIME
static int omap1_pm_runtime_suspend(struct device *dev)
{
	int ret;

	dev_dbg(dev, "%s\n", __func__);

	ret = pm_generic_runtime_suspend(dev);
	if (ret)
		return ret;

	ret = pm_clk_suspend(dev);
	if (ret) {
		pm_generic_runtime_resume(dev);
		return ret;
	}

	return 0;
}

static int omap1_pm_runtime_resume(struct device *dev)
{
	dev_dbg(dev, "%s\n", __func__);

	pm_clk_resume(dev);
	return pm_generic_runtime_resume(dev);
}

static struct dev_pm_domain default_pm_domain = {
	.ops = {
		.runtime_suspend = omap1_pm_runtime_suspend,
		.runtime_resume = omap1_pm_runtime_resume,
		USE_PLATFORM_PM_SLEEP_OPS
	},
};
#define OMAP1_PM_DOMAIN (&default_pm_domain)
#else
#define OMAP1_PM_DOMAIN NULL
#endif /* CONFIG_PM_RUNTIME */

static struct pm_clk_notifier_block platform_bus_notifier = {
	.pm_domain = OMAP1_PM_DOMAIN,
	.con_ids = { "ick", "fck", NULL, },
};

static int __init omap1_pm_runtime_init(void)
{
	if (!cpu_class_is_omap1())
		return -ENODEV;

	pm_clk_add_notifier(&platform_bus_type, &platform_bus_notifier);

	return 0;
}
core_initcall(omap1_pm_runtime_init);

