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
#include <beep/io.h>

#include <mach/regs-clock.h>
#include <plat/gpio-cfg.h>

static void s5pc100_ide_cfg_gpios(unsigned int base, unsigned int nr)
{
	s3c_gpio_cfgrange_nopull(base, nr, S3C_GPIO_SFN(4));

	for (; nr > 0; nr--, base++)
		s5p_gpio_set_drvstr(base, S5P_GPIO_DRVSTR_LV4);
}

void s5pc100_ide_setup_gpio(void)
{
	u32 reg;

	/* Independent CF interface, CF chip select configuration */
	reg = readl(S5PC100_MEM_SYS_CFG) & (~0x3f);
	writel(reg | MEM_SYS_CFG_EBI_FIX_PRI_CFCON, S5PC100_MEM_SYS_CFG);

	/* CF_Add[0 - 2], CF_IORDY, CF_INTRQ, CF_DMARQ, CF_DMARST, CF_DMACK */
	s5pc100_ide_cfg_gpios(S5PC100_GPJ0(0), 8);

	/*CF_Data[0 - 7] */
	s5pc100_ide_cfg_gpios(S5PC100_GPJ2(0), 8);

	/* CF_Data[8 - 15] */
	s5pc100_ide_cfg_gpios(S5PC100_GPJ3(0), 8);

	/* CF_CS0, CF_CS1, CF_IORD, CF_IOWR */
	s5pc100_ide_cfg_gpios(S5PC100_GPJ4(0), 4);

	/* EBI_OE, EBI_WE */
	s3c_gpio_cfgpin_range(S5PC100_GPK0(6), 2, S3C_GPIO_SFN(0));

	/* CF_OE, CF_WE */
	s3c_gpio_cfgrange_nopull(S5PC100_GPK1(6), 8, S3C_GPIO_SFN(2));

	/* CF_CD */
	s3c_gpio_cfgpin(S5PC100_GPK3(5), S3C_GPIO_SFN(2));
	s3c_gpio_setpull(S5PC100_GPK3(5), S3C_GPIO_PULL_NONE);
}
