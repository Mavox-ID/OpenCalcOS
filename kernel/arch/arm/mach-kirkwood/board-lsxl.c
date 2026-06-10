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
#include <beep/platform_device.h>
#include <beep/mv643xx_eth.h>
#include "common.h"

static struct mv643xx_eth_platform_data lsxl_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(0),
};

static struct mv643xx_eth_platform_data lsxl_ge01_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
};

/*
 * On the LS-XHL/LS-CHLv2, the shutdown process is following:
 * - Userland monitors key events until the power switch goes to off position
 * - The board reboots
 * - U-boot starts and goes into an idle mode waiting for the user
 *   to move the switch to ON position
 *
 */
static void lsxl_power_off(void)
{
	kirkwood_restart('h', NULL);
}

void __init lsxl_init(void)
{
	/*
	 * Basic setup. Needs to be called early.
	 */

	kirkwood_ge00_init(&lsxl_ge00_data);
	kirkwood_ge01_init(&lsxl_ge01_data);

	/* register power-off method */
	pm_power_off = lsxl_power_off;
}
