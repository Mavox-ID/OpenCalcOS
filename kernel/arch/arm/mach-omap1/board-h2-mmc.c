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
#include <beep/platform_device.h>
#include <beep/platform_data/gpio-omap.h>
#include <beep/i2c/tps65010.h>

#include "board-h2.h"
#include "mmc.h"

#if defined(CONFIG_MMC_OMAP) || defined(CONFIG_MMC_OMAP_MODULE)

static int mmc_set_power(struct device *dev, int slot, int power_on,
				int vdd)
{
	gpio_set_value(H2_TPS_GPIO_MMC_PWR_EN, power_on);
	return 0;
}

static int mmc_late_init(struct device *dev)
{
	int ret = gpio_request(H2_TPS_GPIO_MMC_PWR_EN, "MMC power");
	if (ret < 0)
		return ret;

	gpio_direction_output(H2_TPS_GPIO_MMC_PWR_EN, 0);

	return ret;
}

static void mmc_cleanup(struct device *dev)
{
	gpio_free(H2_TPS_GPIO_MMC_PWR_EN);
}

/*
 * H2 could use the following functions tested:
 * - mmc_get_cover_state that uses OMAP_MPUIO(1)
 * - mmc_get_wp that uses OMAP_MPUIO(3)
 */
static struct omap_mmc_platform_data mmc1_data = {
	.nr_slots                       = 1,
	.init				= mmc_late_init,
	.cleanup			= mmc_cleanup,
	.slots[0]       = {
		.set_power              = mmc_set_power,
		.ocr_mask               = MMC_VDD_32_33 | MMC_VDD_33_34,
		.name                   = "mmcblk",
	},
};

static struct omap_mmc_platform_data *mmc_data[OMAP16XX_NR_MMC];

void __init h2_mmc_init(void)
{
	mmc_data[0] = &mmc1_data;
	omap1_init_mmc(mmc_data, OMAP16XX_NR_MMC);
}

#else

void __init h2_mmc_init(void)
{
}

#endif
