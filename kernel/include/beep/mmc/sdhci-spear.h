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
#ifndef BEEP_MMC_SDHCI_SPEAR_H
#define BEEP_MMC_SDHCI_SPEAR_H

#include <beep/platform_device.h>
/*
 * struct sdhci_plat_data: spear sdhci platform data structure
 *
 * @card_power_gpio: gpio pin for enabling/disabling power to sdhci socket
 * @power_active_high: if set, enable power to sdhci socket by setting
 *			card_power_gpio
 * @power_always_enb: If set, then enable power on probe, otherwise enable only
 *			on card insertion and disable on card removal.
 * card_int_gpio: gpio pin used for card detection
 */
struct sdhci_plat_data {
	int card_power_gpio;
	int power_active_high;
	int power_always_enb;
	int card_int_gpio;
};

/* This function is used to set platform_data field of pdev->dev */
static inline void
sdhci_set_plat_data(struct platform_device *pdev, struct sdhci_plat_data *data)
{
	pdev->dev.platform_data = data;
}

#endif /* BEEP_MMC_SDHCI_SPEAR_H */
