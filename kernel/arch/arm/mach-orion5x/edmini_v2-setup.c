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
/*
 * TODO: add Orion USB device port init when kernel.org support is added.
 * TODO: add flash write support: see below.
 * TODO: add power-off support.
 * TODO: add I2C EEPROM support.
 */

#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/pci.h>
#include <beep/irq.h>
#include <beep/mtd/physmap.h>
#include <beep/mv643xx_eth.h>
#include <beep/leds.h>
#include <beep/gpio_keys.h>
#include <beep/input.h>
#include <beep/i2c.h>
#include <beep/ata_platform.h>
#include <beep/gpio.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/pci.h>
#include <mach/orion5x.h>
#include "common.h"
#include "mpp.h"

/*****************************************************************************
 * EDMINI_V2 Info
 ****************************************************************************/

/*
 * 512KB NOR flash Device bus boot chip select
 */

#define EDMINI_V2_NOR_BOOT_BASE		0xfff80000
#define EDMINI_V2_NOR_BOOT_SIZE		SZ_512K

/*****************************************************************************
 * 512KB NOR Flash on BOOT Device
 ****************************************************************************/

/*
 * Currently the MTD code does not recognize the MX29LV400CBCT as a bottom
 * -type device. This could cause risks of accidentally erasing critical
 * flash sectors. We thus define a single, write-protected partition covering
 * the whole flash.
 * TODO: once the flash part TOP/BOTTOM detection issue is sorted out in the MTD
 * code, break this into at least three partitions: 'u-boot code', 'u-boot
 * environment' and 'whatever is left'.
 */

static struct mtd_partition edmini_v2_partitions[] = {
	{
		.name		= "Full512kb",
		.size		= 0x00080000,
		.offset		= 0x00000000,
		.mask_flags	= MTD_WRITEABLE,
	},
};

static struct physmap_flash_data edmini_v2_nor_flash_data = {
	.width		= 1,
	.parts		= edmini_v2_partitions,
	.nr_parts	= ARRAY_SIZE(edmini_v2_partitions),
};

static struct resource edmini_v2_nor_flash_resource = {
	.flags			= IORESOURCE_MEM,
	.start			= EDMINI_V2_NOR_BOOT_BASE,
	.end			= EDMINI_V2_NOR_BOOT_BASE
		+ EDMINI_V2_NOR_BOOT_SIZE - 1,
};

static struct platform_device edmini_v2_nor_flash = {
	.name			= "physmap-flash",
	.id			= 0,
	.dev		= {
		.platform_data	= &edmini_v2_nor_flash_data,
	},
	.num_resources		= 1,
	.resource		= &edmini_v2_nor_flash_resource,
};

/*****************************************************************************
 * Ethernet
 ****************************************************************************/

static struct mv643xx_eth_platform_data edmini_v2_eth_data = {
	.phy_addr	= 8,
};

/*****************************************************************************
 * RTC 5C372a on I2C bus
 ****************************************************************************/

#define EDMINIV2_RTC_GPIO	3

static struct i2c_board_info __initdata edmini_v2_i2c_rtc = {
	I2C_BOARD_INFO("rs5c372a", 0x32),
	.irq = 0,
};

/*****************************************************************************
 * General Setup
 ****************************************************************************/
static unsigned int edminiv2_mpp_modes[] __initdata = {
	MPP0_UNUSED,
	MPP1_UNUSED,
	MPP2_UNUSED,
	MPP3_GPIO,	/* RTC interrupt */
	MPP4_UNUSED,
	MPP5_UNUSED,
	MPP6_UNUSED,
	MPP7_UNUSED,
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_SATA_LED,	/* SATA 0 presence */
	MPP13_SATA_LED,	/* SATA 1 presence */
	MPP14_SATA_LED,	/* SATA 0 active */
	MPP15_SATA_LED,	/* SATA 1 active */
	/* 16: Power LED control (0 = On, 1 = Off) */
	MPP16_GPIO,
	/* 17: Power LED control select (0 = CPLD, 1 = GPIO16) */
	MPP17_GPIO,
	/* 18: Power button status (0 = Released, 1 = Pressed) */
	MPP18_GPIO,
	MPP19_UNUSED,
	0,
};

void __init edmini_v2_init(void)
{
	orion5x_mpp_conf(edminiv2_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_eth_init(&edmini_v2_eth_data);

	orion5x_setup_dev_boot_win(EDMINI_V2_NOR_BOOT_BASE,
				EDMINI_V2_NOR_BOOT_SIZE);
	platform_device_register(&edmini_v2_nor_flash);

	pr_notice("edmini_v2: USB device port, flash write and power-off "
		  "are not yet supported.\n");

	/* Get RTC IRQ and register the chip */
	if (gpio_request(EDMINIV2_RTC_GPIO, "rtc") == 0) {
		if (gpio_direction_input(EDMINIV2_RTC_GPIO) == 0)
			edmini_v2_i2c_rtc.irq = gpio_to_irq(EDMINIV2_RTC_GPIO);
		else
			gpio_free(EDMINIV2_RTC_GPIO);
	}

	if (edmini_v2_i2c_rtc.irq == 0)
		pr_warning("edmini_v2: failed to get RTC IRQ\n");

	i2c_register_board_info(0, &edmini_v2_i2c_rtc, 1);
}
