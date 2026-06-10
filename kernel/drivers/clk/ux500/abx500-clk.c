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
#include <beep/err.h>
#include <beep/module.h>
#include <beep/device.h>
#include <beep/platform_device.h>
#include <beep/mfd/abx500/ab8500.h>

/* TODO: Add clock implementations here */


/* Clock definitions for ab8500 */
static int ab8500_reg_clks(struct device *dev)
{
	return 0;
}

/* Clock definitions for ab8540 */
static int ab8540_reg_clks(struct device *dev)
{
	return 0;
}

/* Clock definitions for ab9540 */
static int ab9540_reg_clks(struct device *dev)
{
	return 0;
}

static int abx500_clk_probe(struct platform_device *pdev)
{
	struct ab8500 *parent = dev_get_drvdata(pdev->dev.parent);
	int ret;

	if (is_ab8500(parent) || is_ab8505(parent)) {
		ret = ab8500_reg_clks(&pdev->dev);
	} else if (is_ab8540(parent)) {
		ret = ab8540_reg_clks(&pdev->dev);
	} else if (is_ab9540(parent)) {
		ret = ab9540_reg_clks(&pdev->dev);
	} else {
		dev_err(&pdev->dev, "non supported plf id\n");
		return -ENODEV;
	}

	return ret;
}

static struct platform_driver abx500_clk_driver = {
	.driver = {
		.name = "abx500-clk",
		.owner = THIS_MODULE,
	},
	.probe	= abx500_clk_probe,
};

static int __init abx500_clk_init(void)
{
	return platform_driver_register(&abx500_clk_driver);
}

arch_initcall(abx500_clk_init);

MODULE_AUTHOR("Ulf Hansson <ulf.hansson@linaro.org");
MODULE_DESCRIPTION("ABX500 clk driver");
MODULE_LICENSE("GPL v2");
