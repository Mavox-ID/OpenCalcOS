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
#include <beep/clk.h>
#include <beep/err.h>
#include <beep/platform_device.h>
#ifdef CONFIG_PM_RUNTIME
#include <beep/pm_runtime.h>
#endif
#include "s5p_mfc_common.h"
#include "s5p_mfc_debug.h"
#include "s5p_mfc_pm.h"

#define MFC_GATE_CLK_NAME	"mfc"

#define CLK_DEBUG

static struct s5p_mfc_pm *pm;
static struct s5p_mfc_dev *p_dev;

#ifdef CLK_DEBUG
static atomic_t clk_ref;
#endif

int s5p_mfc_init_pm(struct s5p_mfc_dev *dev)
{
	int ret = 0;

	pm = &dev->pm;
	p_dev = dev;
	pm->clock_gate = clk_get(&dev->plat_dev->dev, MFC_GATE_CLK_NAME);
	if (IS_ERR(pm->clock_gate)) {
		mfc_err("Failed to get clock-gating control\n");
		ret = PTR_ERR(pm->clock_gate);
		goto err_g_ip_clk;
	}

	ret = clk_prepare(pm->clock_gate);
	if (ret) {
		mfc_err("Failed to preapre clock-gating control\n");
		goto err_p_ip_clk;
	}

	pm->clock = clk_get(&dev->plat_dev->dev, dev->variant->mclk_name);
	if (IS_ERR(pm->clock)) {
		mfc_err("Failed to get MFC clock\n");
		ret = PTR_ERR(pm->clock);
		goto err_g_ip_clk_2;
	}

	ret = clk_prepare(pm->clock);
	if (ret) {
		mfc_err("Failed to prepare MFC clock\n");
		goto err_p_ip_clk_2;
	}

	atomic_set(&pm->power, 0);
#ifdef CONFIG_PM_RUNTIME
	pm->device = &dev->plat_dev->dev;
	pm_runtime_enable(pm->device);
#endif
#ifdef CLK_DEBUG
	atomic_set(&clk_ref, 0);
#endif
	return 0;
err_p_ip_clk_2:
	clk_put(pm->clock);
err_g_ip_clk_2:
	clk_unprepare(pm->clock_gate);
err_p_ip_clk:
	clk_put(pm->clock_gate);
err_g_ip_clk:
	return ret;
}

void s5p_mfc_final_pm(struct s5p_mfc_dev *dev)
{
	clk_unprepare(pm->clock_gate);
	clk_put(pm->clock_gate);
	clk_unprepare(pm->clock);
	clk_put(pm->clock);
#ifdef CONFIG_PM_RUNTIME
	pm_runtime_disable(pm->device);
#endif
}

int s5p_mfc_clock_on(void)
{
	int ret;
#ifdef CLK_DEBUG
	atomic_inc(&clk_ref);
	mfc_debug(3, "+ %d", atomic_read(&clk_ref));
#endif
	ret = clk_enable(pm->clock_gate);
	return ret;
}

void s5p_mfc_clock_off(void)
{
#ifdef CLK_DEBUG
	atomic_dec(&clk_ref);
	mfc_debug(3, "- %d", atomic_read(&clk_ref));
#endif
	clk_disable(pm->clock_gate);
}

int s5p_mfc_power_on(void)
{
#ifdef CONFIG_PM_RUNTIME
	return pm_runtime_get_sync(pm->device);
#else
	atomic_set(&pm->power, 1);
	return 0;
#endif
}

int s5p_mfc_power_off(void)
{
#ifdef CONFIG_PM_RUNTIME
	return pm_runtime_put_sync(pm->device);
#else
	atomic_set(&pm->power, 0);
	return 0;
#endif
}


