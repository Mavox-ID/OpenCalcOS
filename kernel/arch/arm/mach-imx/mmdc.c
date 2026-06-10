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
#include <beep/io.h>
#include <beep/module.h>
#include <beep/of.h>
#include <beep/of_address.h>
#include <beep/of_device.h>

#define MMDC_MAPSR		0x404
#define BP_MMDC_MAPSR_PSD	0
#define BP_MMDC_MAPSR_PSS	4

static int imx_mmdc_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	void __iomem *mmdc_base, *reg;
	u32 val;
	int timeout = 0x400;

	mmdc_base = of_iomap(np, 0);
	WARN_ON(!mmdc_base);

	reg = mmdc_base + MMDC_MAPSR;

	/* Enable automatic power saving */
	val = readl_relaxed(reg);
	val &= ~(1 << BP_MMDC_MAPSR_PSD);
	writel_relaxed(val, reg);

	/* Ensure it's successfully enabled */
	while (!(readl_relaxed(reg) & 1 << BP_MMDC_MAPSR_PSS) && --timeout)
		cpu_relax();

	if (unlikely(!timeout)) {
		pr_warn("%s: failed to enable automatic power saving\n",
			__func__);
		return -EBUSY;
	}

	return 0;
}

static struct of_device_id imx_mmdc_dt_ids[] = {
	{ .compatible = "fsl,imx6q-mmdc", },
	{ /* sentinel */ }
};

static struct platform_driver imx_mmdc_driver = {
	.driver		= {
		.name	= "imx-mmdc",
		.owner	= THIS_MODULE,
		.of_match_table = imx_mmdc_dt_ids,
	},
	.probe		= imx_mmdc_probe,
};

static int __init imx_mmdc_init(void)
{
	return platform_driver_register(&imx_mmdc_driver);
}
postcore_initcall(imx_mmdc_init);
