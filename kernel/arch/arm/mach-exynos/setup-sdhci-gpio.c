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

void exynos4_setup_sdhci0_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPK0[0:1] pins to special-function 2 */
	for (gpio = EXYNOS4_GPK0(0); gpio < EXYNOS4_GPK0(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	switch (width) {
	case 8:
		for (gpio = EXYNOS4_GPK1(3); gpio <= EXYNOS4_GPK1(6); gpio++) {
			/* Data pin GPK1[3:6] to special-function 3 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
		}
	case 4:
		for (gpio = EXYNOS4_GPK0(3); gpio <= EXYNOS4_GPK0(6); gpio++) {
			/* Data pin GPK0[3:6] to special-function 2 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
		}
	default:
		break;
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS4_GPK0(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS4_GPK0(2), S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}
}

void exynos4_setup_sdhci1_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPK1[0:1] pins to special-function 2 */
	for (gpio = EXYNOS4_GPK1(0); gpio < EXYNOS4_GPK1(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	for (gpio = EXYNOS4_GPK1(3); gpio <= EXYNOS4_GPK1(6); gpio++) {
		/* Data pin GPK1[3:6] to special-function 2 */
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS4_GPK1(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS4_GPK1(2), S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}
}

void exynos4_setup_sdhci2_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPK2[0:1] pins to special-function 2 */
	for (gpio = EXYNOS4_GPK2(0); gpio < EXYNOS4_GPK2(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	switch (width) {
	case 8:
		for (gpio = EXYNOS4_GPK3(3); gpio <= EXYNOS4_GPK3(6); gpio++) {
			/* Data pin GPK3[3:6] to special-function 3 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
		}
	case 4:
		for (gpio = EXYNOS4_GPK2(3); gpio <= EXYNOS4_GPK2(6); gpio++) {
			/* Data pin GPK2[3:6] to special-function 2 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
		}
	default:
		break;
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS4_GPK2(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS4_GPK2(2), S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}
}

void exynos4_setup_sdhci3_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPK3[0:1] pins to special-function 2 */
	for (gpio = EXYNOS4_GPK3(0); gpio < EXYNOS4_GPK3(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	for (gpio = EXYNOS4_GPK3(3); gpio <= EXYNOS4_GPK3(6); gpio++) {
		/* Data pin GPK3[3:6] to special-function 2 */
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS4_GPK3(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS4_GPK3(2), S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}
}
