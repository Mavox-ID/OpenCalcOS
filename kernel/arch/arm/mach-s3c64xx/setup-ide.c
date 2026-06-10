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

#include <mach/map.h>
#include <mach/regs-clock.h>
#include <plat/gpio-cfg.h>
#include <beep/platform_data/ata-samsung_cf.h>

void s3c64xx_ide_setup_gpio(void)
{
	u32 reg;

	reg = readl(S3C_MEM_SYS_CFG) & (~0x3f);

	/* Independent CF interface, CF chip select configuration */
	writel(reg | MEM_SYS_CFG_INDEP_CF |
		MEM_SYS_CFG_EBI_FIX_PRI_CFCON, S3C_MEM_SYS_CFG);

	s3c_gpio_cfgpin(S3C64XX_GPB(4), S3C_GPIO_SFN(4));

	/* Set XhiDATA[15:0] pins as CF Data[15:0] */
	s3c_gpio_cfgpin_range(S3C64XX_GPK(0), 16, S3C_GPIO_SFN(5));

	/* Set XhiADDR[2:0] pins as CF ADDR[2:0] */
	s3c_gpio_cfgpin_range(S3C64XX_GPL(0), 3, S3C_GPIO_SFN(6));

	/* Set Xhi ctrl pins as CF ctrl pins(IORDY, IOWR, IORD, CE[0:1]) */
	s3c_gpio_cfgpin(S3C64XX_GPM(5), S3C_GPIO_SFN(1));
	s3c_gpio_cfgpin_range(S3C64XX_GPM(0), 5, S3C_GPIO_SFN(6));
}
