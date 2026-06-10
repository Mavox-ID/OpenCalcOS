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
#include <beep/mmc/host.h>
#include <beep/mmc/card.h>

#include <plat/gpio-cfg.h>
#include <plat/regs-sdhci.h>
#include <plat/sdhci.h>

void s5pc100_setup_sdhci0_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int num;

	num = width;
	/* In case of 8 width, we should decrease the 2 */
	if (width == 8)
		num = width - 2;

	/* Set all the necessary GPG0/GPG1 pins to special-function 0 */
	s3c_gpio_cfgrange_nopull(S5PC100_GPG0(0), 2 + num, S3C_GPIO_SFN(2));

	if (width == 8)
		s3c_gpio_cfgrange_nopull(S5PC100_GPG1(0), 2, S3C_GPIO_SFN(2));

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_setpull(S5PC100_GPG1(2), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(S5PC100_GPG1(2), S3C_GPIO_SFN(2));
	}
}

void s5pc100_setup_sdhci1_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;

	/* Set all the necessary GPG2 pins to special-function 2 */
	s3c_gpio_cfgrange_nopull(S5PC100_GPG2(0), 2 + width, S3C_GPIO_SFN(2));

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_setpull(S5PC100_GPG2(6), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(S5PC100_GPG2(6), S3C_GPIO_SFN(2));
	}
}

void s5pc100_setup_sdhci2_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;

	/* Set all the necessary GPG3 pins to special-function 2 */
	s3c_gpio_cfgrange_nopull(S5PC100_GPG3(0), 2 + width, S3C_GPIO_SFN(2));

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_setpull(S5PC100_GPG3(6), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(S5PC100_GPG3(6), S3C_GPIO_SFN(2));
	}
}
