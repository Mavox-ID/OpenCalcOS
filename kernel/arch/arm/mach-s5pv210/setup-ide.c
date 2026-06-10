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
#include <beep/gpio.h>

#include <plat/gpio-cfg.h>

static void s5pv210_ide_cfg_gpios(unsigned int base, unsigned int nr)
{
	s3c_gpio_cfgrange_nopull(base, nr, S3C_GPIO_SFN(4));

	for (; nr > 0; nr--, base++)
		s5p_gpio_set_drvstr(base, S5P_GPIO_DRVSTR_LV4);
}

void s5pv210_ide_setup_gpio(void)
{
	/* CF_Add[0 - 2], CF_IORDY, CF_INTRQ, CF_DMARQ, CF_DMARST, CF_DMACK */
	s5pv210_ide_cfg_gpios(S5PV210_GPJ0(0), 8);

	/* CF_Data[0 - 7] */
	s5pv210_ide_cfg_gpios(S5PV210_GPJ2(0), 8);

	/* CF_Data[8 - 15] */
	s5pv210_ide_cfg_gpios(S5PV210_GPJ3(0), 8);

	/* CF_CS0, CF_CS1, CF_IORD, CF_IOWR */
	s5pv210_ide_cfg_gpios(S5PV210_GPJ4(0), 4);
}
