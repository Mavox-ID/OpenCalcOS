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
#include <beep/pci.h>
#include <beep/ath9k_platform.h>

#include "machtypes.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-spi.h"
#include "dev-usb.h"
#include "dev-wmac.h"
#include "pci.h"

#define DB120_GPIO_LED_WLAN_5G		12
#define DB120_GPIO_LED_WLAN_2G		13
#define DB120_GPIO_LED_STATUS		14
#define DB120_GPIO_LED_WPS		15

#define DB120_GPIO_BTN_WPS		16

#define DB120_KEYS_POLL_INTERVAL	20	/* msecs */
#define DB120_KEYS_DEBOUNCE_INTERVAL	(3 * DB120_KEYS_POLL_INTERVAL)

#define DB120_WMAC_CALDATA_OFFSET 0x1000
#define DB120_PCIE_CALDATA_OFFSET 0x5000

static struct gpio_led db120_leds_gpio[] __initdata = {
	{
		.name		= "db120:green:status",
		.gpio		= DB120_GPIO_LED_STATUS,
		.active_low	= 1,
	},
	{
		.name		= "db120:green:wps",
		.gpio		= DB120_GPIO_LED_WPS,
		.active_low	= 1,
	},
	{
		.name		= "db120:green:wlan-5g",
		.gpio		= DB120_GPIO_LED_WLAN_5G,
		.active_low	= 1,
	},
	{
		.name		= "db120:green:wlan-2g",
		.gpio		= DB120_GPIO_LED_WLAN_2G,
		.active_low	= 1,
	},
};

static struct gpio_keys_button db120_gpio_keys[] __initdata = {
	{
		.desc		= "WPS button",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.debounce_interval = DB120_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= DB120_GPIO_BTN_WPS,
		.active_low	= 1,
	},
};

static struct spi_board_info db120_spi_info[] = {
	{
		.bus_num	= 0,
		.chip_select	= 0,
		.max_speed_hz	= 25000000,
		.modalias	= "s25sl064a",
	}
};

static struct ath79_spi_platform_data db120_spi_data = {
	.bus_num	= 0,
	.num_chipselect	= 1,
};

#ifdef CONFIG_PCI
static struct ath9k_platform_data db120_ath9k_data;

static int db120_pci_plat_dev_init(struct pci_dev *dev)
{
	switch (PCI_SLOT(dev->devfn)) {
	case 0:
		dev->dev.platform_data = &db120_ath9k_data;
		break;
	}

	return 0;
}

static void __init db120_pci_init(u8 *eeprom)
{
	memcpy(db120_ath9k_data.eeprom_data, eeprom,
	       sizeof(db120_ath9k_data.eeprom_data));

	ath79_pci_set_plat_dev_init(db120_pci_plat_dev_init);
	ath79_register_pci();
}
#else
static inline void db120_pci_init(void) {}
#endif /* CONFIG_PCI */

static void __init db120_setup(void)
{
	u8 *art = (u8 *) KSEG1ADDR(0x1fff0000);

	ath79_register_leds_gpio(-1, ARRAY_SIZE(db120_leds_gpio),
				 db120_leds_gpio);
	ath79_register_gpio_keys_polled(-1, DB120_KEYS_POLL_INTERVAL,
					ARRAY_SIZE(db120_gpio_keys),
					db120_gpio_keys);
	ath79_register_spi(&db120_spi_data, db120_spi_info,
			   ARRAY_SIZE(db120_spi_info));
	ath79_register_usb();
	ath79_register_wmac(art + DB120_WMAC_CALDATA_OFFSET);
	db120_pci_init(art + DB120_PCIE_CALDATA_OFFSET);
}

MIPS_MACHINE(ATH79_MACH_DB120, "DB120", "Atheros DB120 reference board",
	     db120_setup);
