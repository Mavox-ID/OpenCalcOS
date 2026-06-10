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
#include <beep/pci.h>
#include <beep/irq.h>
#include <beep/mtd/physmap.h>
#include <beep/timer.h>
#include <beep/mv643xx_eth.h>
#include <beep/ethtool.h>
#include <beep/gpio.h>
#include <beep/leds.h>
#include <beep/input.h>
#include <beep/gpio_keys.h>
#include <beep/spi/flash.h>
#include <beep/spi/spi.h>
#include <net/dsa.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/pci.h>
#include <mach/kirkwood.h>
#include "common.h"
#include "mpp.h"

static struct mv643xx_eth_platform_data mv88f6281gtw_ge_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_NONE,
	.speed		= SPEED_1000,
	.duplex		= DUPLEX_FULL,
};

static struct dsa_chip_data mv88f6281gtw_ge_switch_chip_data = {
	.port_names[0]	= "lan1",
	.port_names[1]	= "lan2",
	.port_names[2]	= "lan3",
	.port_names[3]	= "lan4",
	.port_names[4]	= "wan",
	.port_names[5]	= "cpu",
};

static struct dsa_platform_data mv88f6281gtw_ge_switch_plat_data = {
	.nr_chips	= 1,
	.chip		= &mv88f6281gtw_ge_switch_chip_data,
};

static const struct flash_platform_data mv88f6281gtw_ge_spi_slave_data = {
	.type		= "mx25l12805d",
};

static struct spi_board_info __initdata mv88f6281gtw_ge_spi_slave_info[] = {
	{
		.modalias	= "m25p80",
		.platform_data	= &mv88f6281gtw_ge_spi_slave_data,
		.irq		= -1,
		.max_speed_hz	= 50000000,
		.bus_num	= 0,
		.chip_select	= 0,
	},
};

static struct gpio_keys_button mv88f6281gtw_ge_button_pins[] = {
	{
		.code		= KEY_RESTART,
		.gpio		= 47,
		.desc		= "SWR Button",
		.active_low	= 1,
	}, {
		.code		= KEY_WPS_BUTTON,
		.gpio		= 46,
		.desc		= "WPS Button",
		.active_low	= 1,
	},
};

static struct gpio_keys_platform_data mv88f6281gtw_ge_button_data = {
	.buttons	= mv88f6281gtw_ge_button_pins,
	.nbuttons	= ARRAY_SIZE(mv88f6281gtw_ge_button_pins),
};

static struct platform_device mv88f6281gtw_ge_buttons = {
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources	= 0,
	.dev		= {
		.platform_data	= &mv88f6281gtw_ge_button_data,
	},
};

static struct gpio_led mv88f6281gtw_ge_led_pins[] = {
	{
		.name		= "gtw:green:Status",
		.gpio		= 20,
		.active_low	= 0,
	}, {
		.name		= "gtw:red:Status",
		.gpio		= 21,
		.active_low	= 0,
	}, {
		.name		= "gtw:green:USB",
		.gpio		= 12,
		.active_low	= 0,
	},
};

static struct gpio_led_platform_data mv88f6281gtw_ge_led_data = {
	.leds		= mv88f6281gtw_ge_led_pins,
	.num_leds	= ARRAY_SIZE(mv88f6281gtw_ge_led_pins),
};

static struct platform_device mv88f6281gtw_ge_leds = {
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= {
		.platform_data	= &mv88f6281gtw_ge_led_data,
	},
};

static unsigned int mv88f6281gtw_ge_mpp_config[] __initdata = {
	MPP12_GPO,	/* Status#_USB pin  */
	MPP20_GPIO,	/* Status#_GLED pin */
	MPP21_GPIO,	/* Status#_RLED pin */
	MPP46_GPIO,	/* WPS_Switch pin   */
	MPP47_GPIO,	/* SW_Init pin      */
	0
};

static void __init mv88f6281gtw_ge_init(void)
{
	/*
	 * Basic setup. Needs to be called early.
	 */
	kirkwood_init();
	kirkwood_mpp_conf(mv88f6281gtw_ge_mpp_config);

	kirkwood_ehci_init();
	kirkwood_ge00_init(&mv88f6281gtw_ge_ge00_data);
	kirkwood_ge00_switch_init(&mv88f6281gtw_ge_switch_plat_data, NO_IRQ);
	spi_register_board_info(mv88f6281gtw_ge_spi_slave_info,
				ARRAY_SIZE(mv88f6281gtw_ge_spi_slave_info));
	kirkwood_spi_init();
	kirkwood_uart0_init();
	platform_device_register(&mv88f6281gtw_ge_leds);
	platform_device_register(&mv88f6281gtw_ge_buttons);
}

static int __init mv88f6281gtw_ge_pci_init(void)
{
	if (machine_is_mv88f6281gtw_ge())
		kirkwood_pcie_init(KW_PCIE0);

	return 0;
}
subsys_initcall(mv88f6281gtw_ge_pci_init);

MACHINE_START(MV88F6281GTW_GE, "Marvell 88F6281 GTW GE Board")
	/* Maintainer: Lennert Buytenhek <buytenh@marvell.com> */
	.atag_offset	= 0x100,
	.init_machine	= mv88f6281gtw_ge_init,
	.map_io		= kirkwood_map_io,
	.init_early	= kirkwood_init_early,
	.init_irq	= kirkwood_init_irq,
	.timer		= &kirkwood_timer,
	.restart	= kirkwood_restart,
MACHINE_END
