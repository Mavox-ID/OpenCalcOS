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
#include <asm/mach-ath79/ar71xx_regs.h>
#include "dev-spi.h"

static struct resource ath79_spi_resources[] = {
	{
		.start	= AR71XX_SPI_BASE,
		.end	= AR71XX_SPI_BASE + AR71XX_SPI_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
};

static struct platform_device ath79_spi_device = {
	.name		= "ath79-spi",
	.id		= -1,
	.resource	= ath79_spi_resources,
	.num_resources	= ARRAY_SIZE(ath79_spi_resources),
};

void __init ath79_register_spi(struct ath79_spi_platform_data *pdata,
			       struct spi_board_info const *info,
			       unsigned n)
{
	spi_register_board_info(info, n);
	ath79_spi_device.dev.platform_data = pdata;
	platform_device_register(&ath79_spi_device);
}
