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
#include <beep/module.h>
#include <beep/platform_device.h>
#include <beep/err.h>
#include <beep/slab.h>

#include <beep/platform_data/iommu-omap.h>
#include "omap_hwmod.h"
#include "omap_device.h"

static int __init omap_iommu_dev_init(struct omap_hwmod *oh, void *unused)
{
	struct platform_device *pdev;
	struct iommu_platform_data *pdata;
	struct omap_mmu_dev_attr *a = (struct omap_mmu_dev_attr *)oh->dev_attr;
	static int i;

	pdata = kzalloc(sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	pdata->name = oh->name;
	pdata->nr_tlb_entries = a->nr_tlb_entries;
	pdata->da_start = a->da_start;
	pdata->da_end = a->da_end;

	if (oh->rst_lines_cnt == 1) {
		pdata->reset_name = oh->rst_lines->name;
		pdata->assert_reset = omap_device_assert_hardreset;
		pdata->deassert_reset = omap_device_deassert_hardreset;
	}

	pdev = omap_device_build("omap-iommu", i, oh, pdata, sizeof(*pdata),
				NULL, 0, 0);

	kfree(pdata);

	if (IS_ERR(pdev)) {
		pr_err("%s: device build err: %ld\n", __func__, PTR_ERR(pdev));
		return PTR_ERR(pdev);
	}

	i++;

	return 0;
}

static int __init omap_iommu_init(void)
{
	return omap_hwmod_for_each_by_class("mmu", omap_iommu_dev_init, NULL);
}
/* must be ready before omap3isp is probed */
subsys_initcall(omap_iommu_init);

static void __exit omap_iommu_exit(void)
{
	/* Do nothing */
}
module_exit(omap_iommu_exit);

MODULE_AUTHOR("Hiroshi DOYU");
MODULE_DESCRIPTION("omap iommu: omap device registration");
MODULE_LICENSE("GPL v2");
