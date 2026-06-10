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
#include <beep/delay.h>
#include <beep/err.h>
#include <beep/fsl_devices.h>
#include <beep/platform_device.h>
#include <beep/io.h>

static struct clk *mxc_ahb_clk;
static struct clk *mxc_per_clk;
static struct clk *mxc_ipg_clk;

/* workaround ENGcm09152 for i.MX35 */
#define MX35_USBPHYCTRL_OFFSET		0x600
#define USBPHYCTRL_OTGBASE_OFFSET	0x8
#define USBPHYCTRL_EVDO			(1 << 23)

int fsl_udc_clk_init(struct platform_device *pdev)
{
	struct fsl_usb2_platform_data *pdata;
	unsigned long freq;
	int ret;

	pdata = pdev->dev.platform_data;

	mxc_ipg_clk = devm_clk_get(&pdev->dev, "ipg");
	if (IS_ERR(mxc_ipg_clk)) {
		dev_err(&pdev->dev, "clk_get(\"ipg\") failed\n");
		return PTR_ERR(mxc_ipg_clk);
	}

	mxc_ahb_clk = devm_clk_get(&pdev->dev, "ahb");
	if (IS_ERR(mxc_ahb_clk)) {
		dev_err(&pdev->dev, "clk_get(\"ahb\") failed\n");
		return PTR_ERR(mxc_ahb_clk);
	}

	mxc_per_clk = devm_clk_get(&pdev->dev, "per");
	if (IS_ERR(mxc_per_clk)) {
		dev_err(&pdev->dev, "clk_get(\"per\") failed\n");
		return PTR_ERR(mxc_per_clk);
	}

	clk_prepare_enable(mxc_ipg_clk);
	clk_prepare_enable(mxc_ahb_clk);
	clk_prepare_enable(mxc_per_clk);

	/* make sure USB_CLK is running at 60 MHz +/- 1000 Hz */
	if (!strcmp(pdev->id_entry->name, "imx-udc-mx27")) {
		freq = clk_get_rate(mxc_per_clk);
		if (pdata->phy_mode != FSL_USB2_PHY_ULPI &&
		    (freq < 59999000 || freq > 60001000)) {
			dev_err(&pdev->dev, "USB_CLK=%lu, should be 60MHz\n", freq);
			ret = -EINVAL;
			goto eclkrate;
		}
	}

	return 0;

eclkrate:
	clk_disable_unprepare(mxc_ipg_clk);
	clk_disable_unprepare(mxc_ahb_clk);
	clk_disable_unprepare(mxc_per_clk);
	mxc_per_clk = NULL;
	return ret;
}

int fsl_udc_clk_finalize(struct platform_device *pdev)
{
	struct fsl_usb2_platform_data *pdata = pdev->dev.platform_data;
	int ret = 0;

	/* workaround ENGcm09152 for i.MX35 */
	if (pdata->workaround & FLS_USB2_WORKAROUND_ENGCM09152) {
		unsigned int v;
		struct resource *res = platform_get_resource
			(pdev, IORESOURCE_MEM, 0);
		void __iomem *phy_regs = ioremap(res->start +
						MX35_USBPHYCTRL_OFFSET, 512);
		if (!phy_regs) {
			dev_err(&pdev->dev, "ioremap for phy address fails\n");
			ret = -EINVAL;
			goto ioremap_err;
		}

		v = readl(phy_regs + USBPHYCTRL_OTGBASE_OFFSET);
		writel(v | USBPHYCTRL_EVDO,
			phy_regs + USBPHYCTRL_OTGBASE_OFFSET);

		iounmap(phy_regs);
	}


ioremap_err:
	/* ULPI transceivers don't need usbpll */
	if (pdata->phy_mode == FSL_USB2_PHY_ULPI) {
		clk_disable_unprepare(mxc_per_clk);
		mxc_per_clk = NULL;
	}

	return ret;
}

void fsl_udc_clk_release(void)
{
	if (mxc_per_clk)
		clk_disable_unprepare(mxc_per_clk);
	clk_disable_unprepare(mxc_ahb_clk);
	clk_disable_unprepare(mxc_ipg_clk);
}
