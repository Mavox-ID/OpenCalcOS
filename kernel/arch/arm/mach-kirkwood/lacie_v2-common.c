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
#include <beep/mtd/physmap.h>
#include <beep/spi/flash.h>
#include <beep/spi/spi.h>
#include <beep/i2c.h>
#include <beep/i2c/at24.h>
#include <beep/gpio.h>
#include <asm/mach/time.h>
#include <mach/kirkwood.h>
#include <mach/irqs.h>
#include <plat/time.h>
#include "common.h"
#include "lacie_v2-common.h"

/*****************************************************************************
 * 512KB SPI Flash on Boot Device (MACRONIX MX25L4005)
 ****************************************************************************/

static struct mtd_partition lacie_v2_flash_parts[] = {
	{
		.name = "u-boot",
		.size = MTDPART_SIZ_FULL,
		.offset = 0,
		.mask_flags = MTD_WRITEABLE, /* force read-only */
	},
};

static const struct flash_platform_data lacie_v2_flash = {
	.type		= "mx25l4005a",
	.name		= "spi_flash",
	.parts		= lacie_v2_flash_parts,
	.nr_parts	= ARRAY_SIZE(lacie_v2_flash_parts),
};

static struct spi_board_info __initdata lacie_v2_spi_slave_info[] = {
	{
		.modalias	= "m25p80",
		.platform_data	= &lacie_v2_flash,
		.irq		= -1,
		.max_speed_hz	= 20000000,
		.bus_num	= 0,
		.chip_select	= 0,
	},
};

void __init lacie_v2_register_flash(void)
{
	spi_register_board_info(lacie_v2_spi_slave_info,
				ARRAY_SIZE(lacie_v2_spi_slave_info));
	kirkwood_spi_init();
}

/*****************************************************************************
 * I2C devices
 ****************************************************************************/

static struct at24_platform_data at24c04 = {
	.byte_len	= SZ_4K / 8,
	.page_size	= 16,
};

/*
 * i2c addr | chip         | description
 * 0x50     | HT24LC04     | eeprom (512B)
 */

static struct i2c_board_info __initdata lacie_v2_i2c_info[] = {
	{
		I2C_BOARD_INFO("24c04", 0x50),
		.platform_data  = &at24c04,
	}
};

void __init lacie_v2_register_i2c_devices(void)
{
	kirkwood_i2c_init();
	i2c_register_board_info(0, lacie_v2_i2c_info,
				ARRAY_SIZE(lacie_v2_i2c_info));
}

/*****************************************************************************
 * Hard Disk power
 ****************************************************************************/

static int __initdata lacie_v2_gpio_hdd_power[] = { 16, 17, 41, 42, 43 };

void __init lacie_v2_hdd_power_init(int hdd_num)
{
	int i;
	int err;

	/* Power up all hard disks. */
	for (i = 0; i < hdd_num; i++) {
		err = gpio_request(lacie_v2_gpio_hdd_power[i], NULL);
		if (err == 0) {
			err = gpio_direction_output(
					lacie_v2_gpio_hdd_power[i], 1);
			/* Free the HDD power GPIOs. This allow user-space to
			 * configure them via the gpiolib sysfs interface. */
			gpio_free(lacie_v2_gpio_hdd_power[i]);
		}
		if (err)
			pr_err("Failed to power up HDD%d\n", i + 1);
	}
}
