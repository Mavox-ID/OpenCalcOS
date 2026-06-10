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

/* Number of camera port pins, without FIELD */
#define S3C_CAMIF_NUM_GPIOS	13

/* Default camera port configuration helpers. */

static void camif_get_gpios(int *gpio_start, int *gpio_reset)
{
#ifdef CONFIG_ARCH_S3C24XX
	*gpio_start = S3C2410_GPJ(0);
	*gpio_reset = S3C2410_GPJ(12);
#else
	/* s3c64xx */
	*gpio_start = S3C64XX_GPF(0);
	*gpio_reset = S3C64XX_GPF(3);
#endif
}

int s3c_camif_gpio_get(void)
{
	int gpio_start, gpio_reset;
	int ret, i;

	camif_get_gpios(&gpio_start, &gpio_reset);

	for (i = 0; i < S3C_CAMIF_NUM_GPIOS; i++) {
		int gpio = gpio_start + i;

		if (gpio == gpio_reset)
			continue;

		ret = gpio_request(gpio, "camif");
		if (!ret)
			ret = s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		if (ret) {
			pr_err("failed to configure GPIO %d\n", gpio);
			for (--i; i >= 0; i--)
				gpio_free(gpio--);
			return ret;
		}
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	return 0;
}

void s3c_camif_gpio_put(void)
{
	int i, gpio_start, gpio_reset;

	camif_get_gpios(&gpio_start, &gpio_reset);

	for (i = 0; i < S3C_CAMIF_NUM_GPIOS; i++) {
		int gpio = gpio_start + i;
		if (gpio != gpio_reset)
			gpio_free(gpio);
	}
}
