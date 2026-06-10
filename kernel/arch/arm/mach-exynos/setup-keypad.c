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

void samsung_keypad_cfg_gpio(unsigned int rows, unsigned int cols)
{
	/* Keypads can be of various combinations, Just making sure */

	if (rows > 8) {
		/* Set all the necessary GPX2 pins: KP_ROW[0~7] */
		s3c_gpio_cfgall_range(EXYNOS4_GPX2(0), 8, S3C_GPIO_SFN(3),
					S3C_GPIO_PULL_UP);

		/* Set all the necessary GPX3 pins: KP_ROW[8~] */
		s3c_gpio_cfgall_range(EXYNOS4_GPX3(0), (rows - 8),
					 S3C_GPIO_SFN(3), S3C_GPIO_PULL_UP);
	} else {
		/* Set all the necessary GPX2 pins: KP_ROW[x] */
		s3c_gpio_cfgall_range(EXYNOS4_GPX2(0), rows, S3C_GPIO_SFN(3),
					S3C_GPIO_PULL_UP);
	}

	/* Set all the necessary GPX1 pins to special-function 3: KP_COL[x] */
	s3c_gpio_cfgrange_nopull(EXYNOS4_GPX1(0), cols, S3C_GPIO_SFN(3));
}
