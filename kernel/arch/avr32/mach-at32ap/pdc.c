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
#include <beep/init.h>
#include <beep/platform_device.h>

static int __init pdc_probe(struct platform_device *pdev)
{
	struct clk *pclk, *hclk;

	pclk = clk_get(&pdev->dev, "pclk");
	if (IS_ERR(pclk)) {
		dev_err(&pdev->dev, "no pclk defined\n");
		return PTR_ERR(pclk);
	}
	hclk = clk_get(&pdev->dev, "hclk");
	if (IS_ERR(hclk)) {
		dev_err(&pdev->dev, "no hclk defined\n");
		clk_put(pclk);
		return PTR_ERR(hclk);
	}

	clk_enable(pclk);
	clk_enable(hclk);

	dev_info(&pdev->dev, "Atmel Peripheral DMA Controller enabled\n");
	return 0;
}

static struct platform_driver pdc_driver = {
	.driver		= {
		.name	= "pdc",
	},
};

static int __init pdc_init(void)
{
	return platform_driver_probe(&pdc_driver, pdc_probe);
}
arch_initcall(pdc_init);
