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
#include <beep/spi/spi.h>
#include <beep/spi/flash.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>

#include <mach/dove.h>

#include "common.h"

static struct mv643xx_eth_platform_data cm_a510_ge00_data = {
	.phy_addr	= MV643XX_ETH_PHY_ADDR_DEFAULT,
};

static struct mv_sata_platform_data cm_a510_sata_data = {
	.n_ports        = 1,
};

/*
 * SPI Devices:
 * SPI0: 1M Flash Winbond w25q32bv
 */
static const struct flash_platform_data cm_a510_spi_flash_data = {
	.type		= "w25q32bv",
};

static struct spi_board_info __initdata cm_a510_spi_flash_info[] = {
	{
		.modalias       = "m25p80",
		.platform_data  = &cm_a510_spi_flash_data,
		.irq            = -1,
		.max_speed_hz   = 20000000,
		.bus_num        = 0,
		.chip_select    = 0,
	},
};

static int __init cm_a510_pci_init(void)
{
	if (machine_is_cm_a510())
		dove_pcie_init(1, 1);

	return 0;
}

subsys_initcall(cm_a510_pci_init);

/* Board Init */
static void __init cm_a510_init(void)
{
	/*
	 * Basic Dove setup. Needs to be called early.
	 */
	dove_init();

	dove_ge00_init(&cm_a510_ge00_data);
	dove_ehci0_init();
	dove_ehci1_init();
	dove_sata_init(&cm_a510_sata_data);
	dove_sdio0_init();
	dove_sdio1_init();
	dove_spi0_init();
	dove_spi1_init();
	dove_uart0_init();
	dove_uart1_init();
	dove_i2c_init();
	spi_register_board_info(cm_a510_spi_flash_info,
				ARRAY_SIZE(cm_a510_spi_flash_info));
}

MACHINE_START(CM_A510, "Compulab CM-A510 Board")
	.atag_offset	= 0x100,
	.init_machine	= cm_a510_init,
	.map_io		= dove_map_io,
	.init_early	= dove_init_early,
	.init_irq	= dove_init_irq,
	.timer		= &dove_timer,
	.restart	= dove_restart,
MACHINE_END
