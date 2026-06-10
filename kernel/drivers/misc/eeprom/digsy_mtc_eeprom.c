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
#include <beep/gpio.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/spi/spi.h>
#include <beep/spi/spi_gpio.h>
#include <beep/eeprom_93xx46.h>

#define GPIO_EEPROM_CLK		216
#define GPIO_EEPROM_CS		210
#define GPIO_EEPROM_DI		217
#define GPIO_EEPROM_DO		249
#define GPIO_EEPROM_OE		255
#define EE_SPI_BUS_NUM	1

static void digsy_mtc_op_prepare(void *p)
{
	/* enable */
	gpio_set_value(GPIO_EEPROM_OE, 0);
}

static void digsy_mtc_op_finish(void *p)
{
	/* disable */
	gpio_set_value(GPIO_EEPROM_OE, 1);
}

struct eeprom_93xx46_platform_data digsy_mtc_eeprom_data = {
	.flags		= EE_ADDR8,
	.prepare	= digsy_mtc_op_prepare,
	.finish		= digsy_mtc_op_finish,
};

static struct spi_gpio_platform_data eeprom_spi_gpio_data = {
	.sck		= GPIO_EEPROM_CLK,
	.mosi		= GPIO_EEPROM_DI,
	.miso		= GPIO_EEPROM_DO,
	.num_chipselect	= 1,
};

static struct platform_device digsy_mtc_eeprom = {
	.name	= "spi_gpio",
	.id	= EE_SPI_BUS_NUM,
	.dev	= {
		.platform_data	= &eeprom_spi_gpio_data,
	},
};

static struct spi_board_info digsy_mtc_eeprom_info[] __initdata = {
	{
		.modalias		= "93xx46",
		.max_speed_hz		= 1000000,
		.bus_num		= EE_SPI_BUS_NUM,
		.chip_select		= 0,
		.mode			= SPI_MODE_0,
		.controller_data	= (void *)GPIO_EEPROM_CS,
		.platform_data		= &digsy_mtc_eeprom_data,
	},
};

static int __init digsy_mtc_eeprom_devices_init(void)
{
	int ret;

	ret = gpio_request_one(GPIO_EEPROM_OE, GPIOF_OUT_INIT_HIGH,
				"93xx46 EEPROMs OE");
	if (ret) {
		pr_err("can't request gpio %d\n", GPIO_EEPROM_OE);
		return ret;
	}
	spi_register_board_info(digsy_mtc_eeprom_info,
				ARRAY_SIZE(digsy_mtc_eeprom_info));
	return platform_device_register(&digsy_mtc_eeprom);
}
device_initcall(digsy_mtc_eeprom_devices_init);
