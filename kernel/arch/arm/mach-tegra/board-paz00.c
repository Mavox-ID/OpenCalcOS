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
#include <beep/platform_device.h>
#include <beep/rfkill-gpio.h>
#include "board.h"
#include "board-paz00.h"

static struct rfkill_gpio_platform_data wifi_rfkill_platform_data = {
	.name		= "wifi_rfkill",
	.reset_gpio	= TEGRA_WIFI_RST,
	.shutdown_gpio	= TEGRA_WIFI_PWRN,
	.type	= RFKILL_TYPE_WLAN,
};

static struct platform_device wifi_rfkill_device = {
	.name	= "rfkill_gpio",
	.id	= -1,
	.dev	= {
		.platform_data = &wifi_rfkill_platform_data,
	},
};

void __init tegra_paz00_wifikill_init(void)
{
	platform_device_register(&wifi_rfkill_device);
}
