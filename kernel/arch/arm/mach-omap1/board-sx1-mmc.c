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

#include <mach/hardware.h>
#include <mach/board-sx1.h>

#include "mmc.h"

#if defined(CONFIG_MMC_OMAP) || defined(CONFIG_MMC_OMAP_MODULE)

static int mmc_set_power(struct device *dev, int slot, int power_on,
				int vdd)
{
	int err;
	u8 dat = 0;

	err = sx1_i2c_read_byte(SOFIA_I2C_ADDR, SOFIA_POWER1_REG, &dat);
	if (err < 0)
		return err;

	if (power_on)
		dat |= SOFIA_MMC_POWER;
	else
		dat &= ~SOFIA_MMC_POWER;

	return sx1_i2c_write_byte(SOFIA_I2C_ADDR, SOFIA_POWER1_REG, dat);
}

/* Cover switch is at OMAP_MPUIO(3) */
static struct omap_mmc_platform_data mmc1_data = {
	.nr_slots                       = 1,
	.slots[0]       = {
		.set_power              = mmc_set_power,
		.ocr_mask               = MMC_VDD_32_33 | MMC_VDD_33_34,
		.name                   = "mmcblk",
	},
};

static struct omap_mmc_platform_data *mmc_data[OMAP15XX_NR_MMC];

void __init sx1_mmc_init(void)
{
	mmc_data[0] = &mmc1_data;
	omap1_init_mmc(mmc_data, OMAP15XX_NR_MMC);
}

#else

void __init sx1_mmc_init(void)
{
}

#endif
