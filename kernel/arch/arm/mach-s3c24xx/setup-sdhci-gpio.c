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
#include <beep/types.h>
#include <beep/interrupt.h>
#include <beep/platform_device.h>
#include <beep/io.h>
#include <beep/gpio.h>

#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>

void s3c2416_setup_sdhci0_cfg_gpio(struct platform_device *dev, int width)
{
	s3c_gpio_cfgrange_nopull(S3C2410_GPE(5), 2 + width, S3C_GPIO_SFN(2));
}

void s3c2416_setup_sdhci1_cfg_gpio(struct platform_device *dev, int width)
{
	s3c_gpio_cfgrange_nopull(S3C2410_GPL(0), width, S3C_GPIO_SFN(2));
	s3c_gpio_cfgrange_nopull(S3C2410_GPL(8), 2, S3C_GPIO_SFN(2));
}
