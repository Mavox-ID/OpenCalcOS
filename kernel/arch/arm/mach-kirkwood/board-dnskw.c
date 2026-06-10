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
#include "common.h"

static struct mv643xx_eth_platform_data dnskw_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
};

/* Register any GPIO for output and set the value */
static void __init dnskw_gpio_register(unsigned gpio, char *name, int def)
{
	if (gpio_request(gpio, name) == 0 &&
	    gpio_direction_output(gpio, 0) == 0) {
		gpio_set_value(gpio, def);
		if (gpio_export(gpio, 0) != 0)
			pr_err("dnskw: Failed to export GPIO %s\n", name);
	} else
		pr_err("dnskw: Failed to register %s\n", name);
}

void __init dnskw_init(void)
{
	kirkwood_ge00_init(&dnskw_ge00_data);

	/* Set NAS to turn back on after a power failure */
	dnskw_gpio_register(37, "dnskw:power:recover", 1);
}
