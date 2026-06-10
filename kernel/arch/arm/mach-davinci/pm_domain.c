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
#include <beep/pm_runtime.h>
#include <beep/pm_clock.h>
#include <beep/platform_device.h>

#ifdef CONFIG_PM_RUNTIME
static int davinci_pm_runtime_suspend(struct device *dev)
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

static int davinci_pm_runtime_resume(struct device *dev)
{
	dev_dbg(dev, "%s\n", __func__);

	pm_clk_resume(dev);
	return pm_generic_runtime_resume(dev);
}
#endif

static struct dev_pm_domain davinci_pm_domain = {
	.ops = {
		SET_RUNTIME_PM_OPS(davinci_pm_runtime_suspend,
				   davinci_pm_runtime_resume, NULL)
		USE_PLATFORM_PM_SLEEP_OPS
	},
};

static struct pm_clk_notifier_block platform_bus_notifier = {
	.pm_domain = &davinci_pm_domain,
	.con_ids = { "fck", NULL, },
};

static int __init davinci_pm_runtime_init(void)
{
	pm_clk_add_notifier(&platform_bus_type, &platform_bus_notifier);

	return 0;
}
core_initcall(davinci_pm_runtime_init);
