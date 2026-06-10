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

void s5pv210_setup_sdhci0_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;

	/* Set all the necessary GPG0/GPG1 pins to special-function 2 */
	s3c_gpio_cfgrange_nopull(S5PV210_GPG0(0), 2, S3C_GPIO_SFN(2));

	switch (width) {
	case 8:
		/* GPG1[3:6] special-function 3 */
		s3c_gpio_cfgrange_nopull(S5PV210_GPG1(3), 4, S3C_GPIO_SFN(3));
	case 4:
		/* GPG0[3:6] special-function 2 */
		s3c_gpio_cfgrange_nopull(S5PV210_GPG0(3), 4, S3C_GPIO_SFN(2));
	default:
		break;
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_setpull(S5PV210_GPG0(2), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(S5PV210_GPG0(2), S3C_GPIO_SFN(2));
	}
}

void s5pv210_setup_sdhci1_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;

	/* Set all the necessary GPG1[0:1] pins to special-function 2 */
	s3c_gpio_cfgrange_nopull(S5PV210_GPG1(0), 2, S3C_GPIO_SFN(2));

	/* Data pin GPG1[3:6] to special-function 2 */
	s3c_gpio_cfgrange_nopull(S5PV210_GPG1(3), 4, S3C_GPIO_SFN(2));

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_setpull(S5PV210_GPG1(2), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(S5PV210_GPG1(2), S3C_GPIO_SFN(2));
	}
}

void s5pv210_setup_sdhci2_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;

	/* Set all the necessary GPG2[0:1] pins to special-function 2 */
	s3c_gpio_cfgrange_nopull(S5PV210_GPG2(0), 2, S3C_GPIO_SFN(2));

	switch (width) {
	case 8:
		/* Data pin GPG3[3:6] to special-function 3 */
		s3c_gpio_cfgrange_nopull(S5PV210_GPG3(3), 4, S3C_GPIO_SFN(3));
	case 4:
		/* Data pin GPG2[3:6] to special-function 2 */
		s3c_gpio_cfgrange_nopull(S5PV210_GPG2(3), 4, S3C_GPIO_SFN(2));
	default:
		break;
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_setpull(S5PV210_GPG2(2), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(S5PV210_GPG2(2), S3C_GPIO_SFN(2));
	}
}

void s5pv210_setup_sdhci3_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;

	/* Set all the necessary GPG3[0:1] pins to special-function 2 */
	s3c_gpio_cfgrange_nopull(S5PV210_GPG3(0), 2, S3C_GPIO_SFN(2));

	/* Data pin GPG3[3:6] to special-function 2 */
	s3c_gpio_cfgrange_nopull(S5PV210_GPG3(3), 4, S3C_GPIO_SFN(2));

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_setpull(S5PV210_GPG3(2), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(S5PV210_GPG3(2), S3C_GPIO_SFN(2));
	}
}
