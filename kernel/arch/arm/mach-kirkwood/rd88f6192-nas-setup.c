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
#include <beep/mv643xx_eth.h>
#include <beep/gpio.h>
#include <beep/spi/flash.h>
#include <beep/spi/spi.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/kirkwood.h>
#include <plat/orion-gpio.h>
#include "common.h"

#define RD88F6192_GPIO_USB_VBUS		10

static struct mv643xx_eth_platform_data rd88f6192_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
};

static struct mv_sata_platform_data rd88f6192_sata_data = {
	.n_ports	= 2,
};

static const struct flash_platform_data rd88F6192_spi_slave_data = {
	.type		= "m25p128",
};

static struct spi_board_info __initdata rd88F6192_spi_slave_info[] = {
	{
		.modalias	= "m25p80",
		.platform_data	= &rd88F6192_spi_slave_data,
		.irq		= -1,
		.max_speed_hz	= 20000000,
		.bus_num	= 0,
		.chip_select	= 0,
	},
};

static void __init rd88f6192_init(void)
{
	/*
	 * Basic setup. Needs to be called early.
	 */
	kirkwood_init();

	orion_gpio_set_valid(RD88F6192_GPIO_USB_VBUS, 1);
	if (gpio_request(RD88F6192_GPIO_USB_VBUS, "USB VBUS") != 0 ||
	    gpio_direction_output(RD88F6192_GPIO_USB_VBUS, 1) != 0)
		pr_err("RD-88F6192-NAS: failed to setup USB VBUS GPIO\n");

	kirkwood_ehci_init();
	kirkwood_ge00_init(&rd88f6192_ge00_data);
	kirkwood_sata_init(&rd88f6192_sata_data);
	spi_register_board_info(rd88F6192_spi_slave_info,
				ARRAY_SIZE(rd88F6192_spi_slave_info));
	kirkwood_spi_init();
	kirkwood_uart0_init();
}

static int __init rd88f6192_pci_init(void)
{
	if (machine_is_rd88f6192_nas())
		kirkwood_pcie_init(KW_PCIE0);

	return 0;
}
subsys_initcall(rd88f6192_pci_init);

MACHINE_START(RD88F6192_NAS, "Marvell RD-88F6192-NAS Development Board")
	/* Maintainer: Saeed Bishara <saeed@marvell.com> */
	.atag_offset	= 0x100,
	.init_machine	= rd88f6192_init,
	.map_io		= kirkwood_map_io,
	.init_early	= kirkwood_init_early,
	.init_irq	= kirkwood_init_irq,
	.timer		= &kirkwood_timer,
	.restart	= kirkwood_restart,
MACHINE_END
