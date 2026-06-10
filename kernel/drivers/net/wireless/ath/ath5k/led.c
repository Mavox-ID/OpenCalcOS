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
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <beep/pci.h>
#include "ath5k.h"

#define ATH_SDEVICE(subv, subd) \
	.vendor = PCI_ANY_ID, .device = PCI_ANY_ID, \
	.subvendor = (subv), .subdevice = (subd)

#define ATH_LED(pin, polarity) .driver_data = (((pin) << 8) | (polarity))
#define ATH_PIN(data) ((data) >> 8)
#define ATH_POLARITY(data) ((data) & 0xff)

/* Devices we match on for LED config info (typically laptops) */
static DEFINE_PCI_DEVICE_TABLE(ath5k_led_devices) = {
	/* AR5211 */
	{ PCI_VDEVICE(ATHEROS, PCI_DEVICE_ID_ATHEROS_AR5211), ATH_LED(0, 0) },
	/* HP Compaq nc6xx, nc4000, nx6000 */
	{ ATH_SDEVICE(PCI_VENDOR_ID_COMPAQ, PCI_ANY_ID), ATH_LED(1, 1) },
	/* Acer Aspire One A150 (maximlevitsky@gmail.com) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_FOXCONN, 0xe008), ATH_LED(3, 0) },
	/* Acer Aspire One AO531h AO751h (keng-yu.lin@canonical.com) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_FOXCONN, 0xe00d), ATH_LED(3, 0) },
	/* Acer Ferrari 5000 (russ.dill@gmail.com) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_AMBIT, 0x0422), ATH_LED(1, 1) },
	/* E-machines E510 (tuliom@gmail.com) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_AMBIT, 0x0428), ATH_LED(3, 0) },
	/* BenQ Joybook R55v (nowymarluk@wp.pl) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_QMI, 0x0100), ATH_LED(1, 0) },
	/* Acer Extensa 5620z (nekoreeve@gmail.com) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_QMI, 0x0105), ATH_LED(3, 0) },
	/* Fukato Datacask Jupiter 1014a (mrb74@gmx.at) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_AZWAVE, 0x1026), ATH_LED(3, 0) },
	/* IBM ThinkPad AR5BXB6 (legovini@spiro.fisica.unipd.it) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_IBM, 0x058a), ATH_LED(1, 0) },
	/* HP Compaq CQ60-206US (ddreggors@jumptv.com) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_HP, 0x0137a), ATH_LED(3, 1) },
	/* HP Compaq C700 (nitrousnrg@gmail.com) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_HP, 0x0137b), ATH_LED(3, 1) },
	/* LiteOn AR5BXB63 (magooz@salug.it) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_ATHEROS, 0x3067), ATH_LED(3, 0) },
	/* IBM-specific AR5212 (all others) */
	{ PCI_VDEVICE(ATHEROS, PCI_DEVICE_ID_ATHEROS_AR5212_IBM), ATH_LED(0, 0) },
	/* Dell Vostro A860 (shahar@shahar-or.co.il) */
	{ ATH_SDEVICE(PCI_VENDOR_ID_QMI, 0x0112), ATH_LED(3, 0) },
	{ }
};

void ath5k_led_enable(struct ath5k_hw *ah)
{
	if (test_bit(ATH_STAT_LEDSOFT, ah->status)) {
		ath5k_hw_set_gpio_output(ah, ah->led_pin);
		ath5k_led_off(ah);
	}
}

static void ath5k_led_on(struct ath5k_hw *ah)
{
	if (!test_bit(ATH_STAT_LEDSOFT, ah->status))
		return;
	ath5k_hw_set_gpio(ah, ah->led_pin, ah->led_on);
}

void ath5k_led_off(struct ath5k_hw *ah)
{
	if (!test_bit(ATH_STAT_LEDSOFT, ah->status))
		return;
	ath5k_hw_set_gpio(ah, ah->led_pin, !ah->led_on);
}

static void
ath5k_led_brightness_set(struct led_classdev *led_dev,
	enum led_brightness brightness)
{
	struct ath5k_led *led = container_of(led_dev, struct ath5k_led,
		led_dev);

	if (brightness == LED_OFF)
		ath5k_led_off(led->ah);
	else
		ath5k_led_on(led->ah);
}

static int
ath5k_register_led(struct ath5k_hw *ah, struct ath5k_led *led,
		   const char *name, char *trigger)
{
	int err;

	led->ah = ah;
	strncpy(led->name, name, sizeof(led->name));
	led->led_dev.name = led->name;
	led->led_dev.default_trigger = trigger;
	led->led_dev.brightness_set = ath5k_led_brightness_set;

	err = led_classdev_register(ah->dev, &led->led_dev);
	if (err) {
		ATH5K_WARN(ah, "could not register LED %s\n", name);
		led->ah = NULL;
	}
	return err;
}

static void
ath5k_unregister_led(struct ath5k_led *led)
{
	if (!led->ah)
		return;
	led_classdev_unregister(&led->led_dev);
	ath5k_led_off(led->ah);
	led->ah = NULL;
}

void ath5k_unregister_leds(struct ath5k_hw *ah)
{
	ath5k_unregister_led(&ah->rx_led);
	ath5k_unregister_led(&ah->tx_led);
}

int ath5k_init_leds(struct ath5k_hw *ah)
{
	int ret = 0;
	struct ieee80211_hw *hw = ah->hw;
#ifndef CONFIG_ATHEROS_AR231X
	struct pci_dev *pdev = ah->pdev;
#endif
	char name[ATH5K_LED_MAX_NAME_LEN + 1];
	const struct pci_device_id *match;

	if (!ah->pdev)
		return 0;

#ifdef CONFIG_ATHEROS_AR231X
	match = NULL;
#else
	match = pci_match_id(&ath5k_led_devices[0], pdev);
#endif
	if (match) {
		__set_bit(ATH_STAT_LEDSOFT, ah->status);
		ah->led_pin = ATH_PIN(match->driver_data);
		ah->led_on = ATH_POLARITY(match->driver_data);
	}

	if (!test_bit(ATH_STAT_LEDSOFT, ah->status))
		goto out;

	ath5k_led_enable(ah);

	snprintf(name, sizeof(name), "ath5k-%s::rx", wiphy_name(hw->wiphy));
	ret = ath5k_register_led(ah, &ah->rx_led, name,
		ieee80211_get_rx_led_name(hw));
	if (ret)
		goto out;

	snprintf(name, sizeof(name), "ath5k-%s::tx", wiphy_name(hw->wiphy));
	ret = ath5k_register_led(ah, &ah->tx_led, name,
		ieee80211_get_tx_led_name(hw));
out:
	return ret;
}

