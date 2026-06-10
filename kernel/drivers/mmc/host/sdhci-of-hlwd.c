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
#include <beep/module.h>
#include <beep/mmc/host.h>
#include "sdhci-pltfm.h"

/*
 * Ops and quirks for the Nintendo Wii SDHCI controllers.
 */

/*
 * We need a small delay after each write, or things go horribly wrong.
 */
#define SDHCI_HLWD_WRITE_DELAY	5 /* usecs */

static void sdhci_hlwd_writel(struct sdhci_host *host, u32 val, int reg)
{
	sdhci_be32bs_writel(host, val, reg);
	udelay(SDHCI_HLWD_WRITE_DELAY);
}

static void sdhci_hlwd_writew(struct sdhci_host *host, u16 val, int reg)
{
	sdhci_be32bs_writew(host, val, reg);
	udelay(SDHCI_HLWD_WRITE_DELAY);
}

static void sdhci_hlwd_writeb(struct sdhci_host *host, u8 val, int reg)
{
	sdhci_be32bs_writeb(host, val, reg);
	udelay(SDHCI_HLWD_WRITE_DELAY);
}

static struct sdhci_ops sdhci_hlwd_ops = {
	.read_l = sdhci_be32bs_readl,
	.read_w = sdhci_be32bs_readw,
	.read_b = sdhci_be32bs_readb,
	.write_l = sdhci_hlwd_writel,
	.write_w = sdhci_hlwd_writew,
	.write_b = sdhci_hlwd_writeb,
};

static struct sdhci_pltfm_data sdhci_hlwd_pdata = {
	.quirks = SDHCI_QUIRK_32BIT_DMA_ADDR |
		  SDHCI_QUIRK_32BIT_DMA_SIZE,
	.ops = &sdhci_hlwd_ops,
};

static int sdhci_hlwd_probe(struct platform_device *pdev)
{
	return sdhci_pltfm_register(pdev, &sdhci_hlwd_pdata);
}

static int sdhci_hlwd_remove(struct platform_device *pdev)
{
	return sdhci_pltfm_unregister(pdev);
}

static const struct of_device_id sdhci_hlwd_of_match[] = {
	{ .compatible = "nintendo,hollywood-sdhci" },
	{ }
};
MODULE_DEVICE_TABLE(of, sdhci_hlwd_of_match);

static struct platform_driver sdhci_hlwd_driver = {
	.driver = {
		.name = "sdhci-hlwd",
		.owner = THIS_MODULE,
		.of_match_table = sdhci_hlwd_of_match,
		.pm = SDHCI_PLTFM_PMOPS,
	},
	.probe = sdhci_hlwd_probe,
	.remove = sdhci_hlwd_remove,
};

module_platform_driver(sdhci_hlwd_driver);

MODULE_DESCRIPTION("Nintendo Wii SDHCI OF driver");
MODULE_AUTHOR("The GameCube Beep Team, Albert Herranz");
MODULE_LICENSE("GPL v2");
