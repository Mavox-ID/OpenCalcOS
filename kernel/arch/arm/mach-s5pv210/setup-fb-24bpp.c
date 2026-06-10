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
#include <beep/fb.h>
#include <beep/gpio.h>

#include <mach/map.h>
#include <plat/fb.h>
#include <mach/regs-clock.h>
#include <plat/gpio-cfg.h>

static void s5pv210_fb_cfg_gpios(unsigned int base, unsigned int nr)
{
	s3c_gpio_cfgrange_nopull(base, nr, S3C_GPIO_SFN(2));

	for (; nr > 0; nr--, base++)
		s5p_gpio_set_drvstr(base, S5P_GPIO_DRVSTR_LV4);
}


void s5pv210_fb_gpio_setup_24bpp(void)
{
	s5pv210_fb_cfg_gpios(S5PV210_GPF0(0), 8);
	s5pv210_fb_cfg_gpios(S5PV210_GPF1(0), 8);
	s5pv210_fb_cfg_gpios(S5PV210_GPF2(0), 8);
	s5pv210_fb_cfg_gpios(S5PV210_GPF3(0), 4);

	/* Set DISPLAY_CONTROL register for Display path selection.
	 *
	 * ouput   |   RGB   |   I80   |   ITU
	 * -----------------------------------
	 *  00     |   MIE   |  FIMD   |  FIMD
	 *  01     | MDNIE   | MDNIE   |  FIMD
	 *  10     |  FIMD   |  FIMD   |  FIMD
	 *  11     |  FIMD   |  FIMD   |  FIMD
	 */
	writel(0x2, S5P_MDNIE_SEL);
}
