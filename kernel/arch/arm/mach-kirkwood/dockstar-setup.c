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
#include <beep/ata_platform.h>
#include <beep/mtd/partitions.h>
#include <beep/mv643xx_eth.h>
#include <beep/gpio.h>
#include <beep/leds.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/kirkwood.h>
#include <beep/platform_data/mmc-mvsdio.h>
#include "common.h"
#include "mpp.h"

static struct mtd_partition dockstar_nand_parts[] = {
	{
		.name = "u-boot",
		.offset = 0,
		.size = SZ_1M
	}, {
		.name = "uImage",
		.offset = MTDPART_OFS_NXTBLK,
		.size = SZ_4M
	}, {
		.name = "root",
		.offset = MTDPART_OFS_NXTBLK,
		.size = MTDPART_SIZ_FULL
	},
};

static struct mv643xx_eth_platform_data dockstar_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(0),
};

static struct gpio_led dockstar_led_pins[] = {
	{
		.name			= "dockstar:green:health",
		.default_trigger	= "default-on",
		.gpio			= 46,
		.active_low		= 1,
	},
	{
		.name			= "dockstar:orange:misc",
		.default_trigger	= "none",
		.gpio			= 47,
		.active_low		= 1,
	},
};

static struct gpio_led_platform_data dockstar_led_data = {
	.leds		= dockstar_led_pins,
	.num_leds	= ARRAY_SIZE(dockstar_led_pins),
};

static struct platform_device dockstar_leds = {
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= {
		.platform_data	= &dockstar_led_data,
	}
};

static unsigned int dockstar_mpp_config[] __initdata = {
	MPP29_GPIO,	/* USB Power Enable */
	MPP46_GPIO,	/* LED green */
	MPP47_GPIO,	/* LED orange */
	0
};

static void __init dockstar_init(void)
{
	/*
	 * Basic setup. Needs to be called early.
	 */
	kirkwood_init();

	/* setup gpio pin select */
	kirkwood_mpp_conf(dockstar_mpp_config);

	kirkwood_uart0_init();
	kirkwood_nand_init(ARRAY_AND_SIZE(dockstar_nand_parts), 25);

	if (gpio_request(29, "USB Power Enable") != 0 ||
	    gpio_direction_output(29, 1) != 0)
		pr_err("can't set up GPIO 29 (USB Power Enable)\n");
	kirkwood_ehci_init();

	kirkwood_ge00_init(&dockstar_ge00_data);

	platform_device_register(&dockstar_leds);
}

MACHINE_START(DOCKSTAR, "Seagate FreeAgent DockStar")
	.atag_offset	= 0x100,
	.init_machine	= dockstar_init,
	.map_io		= kirkwood_map_io,
	.init_early	= kirkwood_init_early,
	.init_irq	= kirkwood_init_irq,
	.timer		= &kirkwood_timer,
	.restart	= kirkwood_restart,
MACHINE_END
