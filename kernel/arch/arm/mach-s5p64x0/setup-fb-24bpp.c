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
#include <beep/fb.h>
#include <beep/gpio.h>

#include <plat/cpu.h>
#include <plat/fb.h>
#include <plat/gpio-cfg.h>

void s5p64x0_fb_gpio_setup_24bpp(void)
{
	if (soc_is_s5p6440()) {
		s3c_gpio_cfgrange_nopull(S5P6440_GPI(0), 16, S3C_GPIO_SFN(2));
		s3c_gpio_cfgrange_nopull(S5P6440_GPJ(0), 12, S3C_GPIO_SFN(2));
	} else if (soc_is_s5p6450()) {
		s3c_gpio_cfgrange_nopull(S5P6450_GPI(0), 16, S3C_GPIO_SFN(2));
		s3c_gpio_cfgrange_nopull(S5P6450_GPJ(0), 12, S3C_GPIO_SFN(2));
	}
}
