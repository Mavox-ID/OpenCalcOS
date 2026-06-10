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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/mv643xx_eth.h>
#include <beep/gpio.h>
#include <beep/platform_data/mmc-mvsdio.h>
#include "common.h"

static struct mv643xx_eth_platform_data dreamplug_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(0),
};

static struct mv643xx_eth_platform_data dreamplug_ge01_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(1),
};

static struct mvsdio_platform_data dreamplug_mvsdio_data = {
	/* unfortunately the CD signal has not been connected */
};

void __init dreamplug_init(void)
{
	/*
	 * Basic setup. Needs to be called early.
	 */
	kirkwood_ge00_init(&dreamplug_ge00_data);
	kirkwood_ge01_init(&dreamplug_ge01_data);
	kirkwood_sdio_init(&dreamplug_mvsdio_data);
}
