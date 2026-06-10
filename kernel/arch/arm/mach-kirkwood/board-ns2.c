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
#include <beep/gpio.h>
#include <beep/of.h>
#include "common.h"

static struct mv643xx_eth_platform_data ns2_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
};

#define NS2_GPIO_POWER_OFF	31

static void ns2_power_off(void)
{
	gpio_set_value(NS2_GPIO_POWER_OFF, 1);
}

void __init ns2_init(void)
{
	/*
	 * Basic setup. Needs to be called early.
	 */
	if (of_machine_is_compatible("lacie,netspace_lite_v2") ||
	    of_machine_is_compatible("lacie,netspace_mini_v2"))
		ns2_ge00_data.phy_addr = MV643XX_ETH_PHY_ADDR(0);
	kirkwood_ge00_init(&ns2_ge00_data);

	if (gpio_request(NS2_GPIO_POWER_OFF, "power-off") == 0 &&
	    gpio_direction_output(NS2_GPIO_POWER_OFF, 0) == 0)
		pm_power_off = ns2_power_off;
	else
		pr_err("ns2: failed to configure power-off GPIO\n");
}
