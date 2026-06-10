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
struct platform_device; /* don't need the contents */

#include <beep/gpio.h>
#include <beep/platform_data/i2c-s3c2410.h>
#include <plat/gpio-cfg.h>

void s3c_i2c5_cfg_gpio(struct platform_device *dev)
{
	s3c_gpio_cfgall_range(EXYNOS4_GPB(6), 2,
			      S3C_GPIO_SFN(3), S3C_GPIO_PULL_UP);
}
