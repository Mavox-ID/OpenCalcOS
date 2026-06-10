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
#include <plat/gpio-cfg.h>

#ifdef CONFIG_S3C64XX_DEV_SPI0
int s3c64xx_spi0_cfg_gpio(void)
{
	s3c_gpio_cfgpin(S5PV210_GPB(0), S3C_GPIO_SFN(2));
	s3c_gpio_setpull(S5PV210_GPB(0), S3C_GPIO_PULL_UP);
	s3c_gpio_cfgall_range(S5PV210_GPB(2), 2,
				S3C_GPIO_SFN(2), S3C_GPIO_PULL_UP);
	return 0;
}
#endif

#ifdef CONFIG_S3C64XX_DEV_SPI1
int s3c64xx_spi1_cfg_gpio(void)
{
	s3c_gpio_cfgpin(S5PV210_GPB(4), S3C_GPIO_SFN(2));
	s3c_gpio_setpull(S5PV210_GPB(4), S3C_GPIO_PULL_UP);
	s3c_gpio_cfgall_range(S5PV210_GPB(6), 2,
				S3C_GPIO_SFN(2), S3C_GPIO_PULL_UP);
	return 0;
}
#endif
