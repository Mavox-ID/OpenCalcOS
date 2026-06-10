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
#include <beep/platform_device.h>
#include <beep/io.h>
#include <beep/gpio.h>

#include <mach/regs-gpio.h>
#include <mach/regs-clock.h>

#include <plat/gpio-cfg.h>
#include <plat/sdhci.h>
#include <plat/cpu.h>

void s5p64x0_setup_sdhci0_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;

	/* Set all the necessary GPG pins to special-function 2 */
	if (soc_is_s5p6450())
		s3c_gpio_cfgrange_nopull(S5P6450_GPG(0), 2 + width,
					 S3C_GPIO_SFN(2));
	else
		s3c_gpio_cfgrange_nopull(S5P6440_GPG(0), 2 + width,
					 S3C_GPIO_SFN(2));

	/* Set GPG[6] pin to special-function 2 - MMC0 CDn */
	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		if (soc_is_s5p6450()) {
			s3c_gpio_setpull(S5P6450_GPG(6), S3C_GPIO_PULL_UP);
			s3c_gpio_cfgpin(S5P6450_GPG(6), S3C_GPIO_SFN(2));
		} else {
			s3c_gpio_setpull(S5P6440_GPG(6), S3C_GPIO_PULL_UP);
			s3c_gpio_cfgpin(S5P6440_GPG(6), S3C_GPIO_SFN(2));
		}
	}
}

void s5p64x0_setup_sdhci1_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;

	/* Set GPH[0:1] pins to special-function 2 - CLK and CMD */
	if (soc_is_s5p6450())
		s3c_gpio_cfgrange_nopull(S5P6450_GPH(0), 2, S3C_GPIO_SFN(2));
	else
		s3c_gpio_cfgrange_nopull(S5P6440_GPH(0), 2 , S3C_GPIO_SFN(2));

	switch (width) {
	case 8:
		/* Set data pins GPH[6:9] special-function 2 */
		if (soc_is_s5p6450())
			s3c_gpio_cfgrange_nopull(S5P6450_GPH(6), 4,
						 S3C_GPIO_SFN(2));
		else
			s3c_gpio_cfgrange_nopull(S5P6440_GPH(6), 4,
						 S3C_GPIO_SFN(2));
	case 4:
		/* set data pins GPH[2:5] special-function 2 */
		if (soc_is_s5p6450())
			s3c_gpio_cfgrange_nopull(S5P6450_GPH(2), 4,
						 S3C_GPIO_SFN(2));
		else
			s3c_gpio_cfgrange_nopull(S5P6440_GPH(2), 4,
						 S3C_GPIO_SFN(2));
	default:
		break;
	}

	/* Set GPG[6] pin to special-funtion 3 : MMC1 CDn */
	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		if (soc_is_s5p6450()) {
			s3c_gpio_setpull(S5P6450_GPG(6), S3C_GPIO_PULL_UP);
			s3c_gpio_cfgpin(S5P6450_GPG(6), S3C_GPIO_SFN(3));
		} else {
			s3c_gpio_setpull(S5P6440_GPG(6), S3C_GPIO_PULL_UP);
			s3c_gpio_cfgpin(S5P6440_GPG(6), S3C_GPIO_SFN(3));
		}
	}
}

void s5p6440_setup_sdhci2_cfg_gpio(struct platform_device *dev, int width)
{
	/* Set GPC[4:5] pins to special-function 3 - CLK and CMD */
	s3c_gpio_cfgrange_nopull(S5P6440_GPC(4), 2, S3C_GPIO_SFN(3));

	/* Set data pins GPH[6:9] pins to special-function 3 */
	s3c_gpio_cfgrange_nopull(S5P6440_GPH(6), 4, S3C_GPIO_SFN(3));
}

void s5p6450_setup_sdhci2_cfg_gpio(struct platform_device *dev, int width)
{
	/* Set all the necessary GPG pins to special-function 3 */
	s3c_gpio_cfgrange_nopull(S5P6450_GPG(7), 2 + width, S3C_GPIO_SFN(3));
}
