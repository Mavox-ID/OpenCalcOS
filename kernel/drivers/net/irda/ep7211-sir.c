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

#include <mach/hardware.h>

#include "sir-dev.h"

static int clps711x_dongle_open(struct sir_dev *dev)
{
	unsigned int syscon;

	/* Turn on the SIR encoder. */
	syscon = clps_readl(SYSCON1);
	syscon |= SYSCON1_SIREN;
	clps_writel(syscon, SYSCON1);

	return 0;
}

static int clps711x_dongle_close(struct sir_dev *dev)
{
	unsigned int syscon;

	/* Turn off the SIR encoder. */
	syscon = clps_readl(SYSCON1);
	syscon &= ~SYSCON1_SIREN;
	clps_writel(syscon, SYSCON1);

	return 0;
}

static struct dongle_driver clps711x_dongle = {
	.owner		= THIS_MODULE,
	.driver_name	= "EP7211 IR driver",
	.type		= IRDA_EP7211_DONGLE,
	.open		= clps711x_dongle_open,
	.close		= clps711x_dongle_close,
};

static int clps711x_sir_probe(struct platform_device *pdev)
{
	return irda_register_dongle(&clps711x_dongle);
}

static int clps711x_sir_remove(struct platform_device *pdev)
{
	return irda_unregister_dongle(&clps711x_dongle);
}

static struct platform_driver clps711x_sir_driver = {
	.driver	= {
		.name	= "sir-clps711x",
		.owner	= THIS_MODULE,
	},
	.probe	= clps711x_sir_probe,
	.remove	= clps711x_sir_remove,
};
module_platform_driver(clps711x_sir_driver);

MODULE_AUTHOR("Samuel Ortiz <samuel@sortiz.org>");
MODULE_DESCRIPTION("EP7211 IR dongle driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("irda-dongle-13"); /* IRDA_EP7211_DONGLE */
