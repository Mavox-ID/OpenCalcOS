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
#include <beep/delay.h>
#include <beep/device.h>
#include <beep/mmc/host.h>
#include <beep/module.h>
#include <mach/cns3xxx.h>
#include "sdhci-pltfm.h"

static unsigned int sdhci_cns3xxx_get_max_clk(struct sdhci_host *host)
{
	return 150000000;
}

static void sdhci_cns3xxx_set_clock(struct sdhci_host *host, unsigned int clock)
{
	struct device *dev = mmc_dev(host->mmc);
	int div = 1;
	u16 clk;
	unsigned long timeout;

	if (clock == host->clock)
		return;

	sdhci_writew(host, 0, SDHCI_CLOCK_CONTROL);

	if (clock == 0)
		goto out;

	while (host->max_clk / div > clock) {
		/*
		 * On CNS3xxx divider grows linearly up to 4, and then
		 * exponentially up to 256.
		 */
		if (div < 4)
			div += 1;
		else if (div < 256)
			div *= 2;
		else
			break;
	}

	dev_dbg(dev, "desired SD clock: %d, actual: %d\n",
		clock, host->max_clk / div);

	/* Divide by 3 is special. */
	if (div != 3)
		div >>= 1;

	clk = div << SDHCI_DIVIDER_SHIFT;
	clk |= SDHCI_CLOCK_INT_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

	timeout = 20;
	while (!((clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL))
			& SDHCI_CLOCK_INT_STABLE)) {
		if (timeout == 0) {
			dev_warn(dev, "clock is unstable");
			break;
		}
		timeout--;
		mdelay(1);
	}

	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
out:
	host->clock = clock;
}

static struct sdhci_ops sdhci_cns3xxx_ops = {
	.get_max_clock	= sdhci_cns3xxx_get_max_clk,
	.set_clock	= sdhci_cns3xxx_set_clock,
};

static struct sdhci_pltfm_data sdhci_cns3xxx_pdata = {
	.ops = &sdhci_cns3xxx_ops,
	.quirks = SDHCI_QUIRK_BROKEN_DMA |
		  SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_INVERTED_WRITE_PROTECT |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN |
		  SDHCI_QUIRK_BROKEN_TIMEOUT_VAL |
		  SDHCI_QUIRK_NONSTANDARD_CLOCK,
};

static int sdhci_cns3xxx_probe(struct platform_device *pdev)
{
	return sdhci_pltfm_register(pdev, &sdhci_cns3xxx_pdata);
}

static int sdhci_cns3xxx_remove(struct platform_device *pdev)
{
	return sdhci_pltfm_unregister(pdev);
}

static struct platform_driver sdhci_cns3xxx_driver = {
	.driver		= {
		.name	= "sdhci-cns3xxx",
		.owner	= THIS_MODULE,
		.pm	= SDHCI_PLTFM_PMOPS,
	},
	.probe		= sdhci_cns3xxx_probe,
	.remove		= sdhci_cns3xxx_remove,
};

module_platform_driver(sdhci_cns3xxx_driver);

MODULE_DESCRIPTION("SDHCI driver for CNS3xxx");
MODULE_AUTHOR("Scott Shu, "
	      "Anton Vorontsov <avorontsov@mvista.com>");
MODULE_LICENSE("GPL v2");
