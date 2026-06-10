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
#include <plat/keypad.h>

void samsung_keypad_cfg_gpio(unsigned int rows, unsigned int cols)
{
	/* Set all the necessary GPK pins to special-function 3: KP_ROW[x] */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPK(8), rows, S3C_GPIO_SFN(3));

	/* Set all the necessary GPL pins to special-function 3: KP_COL[x] */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPL(0), cols, S3C_GPIO_SFN(3));
}
