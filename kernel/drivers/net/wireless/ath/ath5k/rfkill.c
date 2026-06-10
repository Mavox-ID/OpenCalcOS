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
#include "ath5k.h"


static inline void ath5k_rfkill_disable(struct ath5k_hw *ah)
{
	ATH5K_DBG(ah, ATH5K_DEBUG_ANY, "rfkill disable (gpio:%d polarity:%d)\n",
		ah->rf_kill.gpio, ah->rf_kill.polarity);
	ath5k_hw_set_gpio_output(ah, ah->rf_kill.gpio);
	ath5k_hw_set_gpio(ah, ah->rf_kill.gpio, !ah->rf_kill.polarity);
}


static inline void ath5k_rfkill_enable(struct ath5k_hw *ah)
{
	ATH5K_DBG(ah, ATH5K_DEBUG_ANY, "rfkill enable (gpio:%d polarity:%d)\n",
		ah->rf_kill.gpio, ah->rf_kill.polarity);
	ath5k_hw_set_gpio_output(ah, ah->rf_kill.gpio);
	ath5k_hw_set_gpio(ah, ah->rf_kill.gpio, ah->rf_kill.polarity);
}

static inline void ath5k_rfkill_set_intr(struct ath5k_hw *ah, bool enable)
{
	u32 curval;

	ath5k_hw_set_gpio_input(ah, ah->rf_kill.gpio);
	curval = ath5k_hw_get_gpio(ah, ah->rf_kill.gpio);
	ath5k_hw_set_gpio_intr(ah, ah->rf_kill.gpio, enable ?
					!!curval : !curval);
}

static bool
ath5k_is_rfkill_set(struct ath5k_hw *ah)
{
	/* configuring GPIO for input for some reason disables rfkill */
	/*ath5k_hw_set_gpio_input(ah, ah->rf_kill.gpio);*/
	return ath5k_hw_get_gpio(ah, ah->rf_kill.gpio) ==
							ah->rf_kill.polarity;
}

static void
ath5k_tasklet_rfkill_toggle(unsigned long data)
{
	struct ath5k_hw *ah = (void *)data;
	bool blocked;

	blocked = ath5k_is_rfkill_set(ah);
	wiphy_rfkill_set_hw_state(ah->hw->wiphy, blocked);
}


void
ath5k_rfkill_hw_start(struct ath5k_hw *ah)
{
	/* read rfkill GPIO configuration from EEPROM header */
	ah->rf_kill.gpio = ah->ah_capabilities.cap_eeprom.ee_rfkill_pin;
	ah->rf_kill.polarity = ah->ah_capabilities.cap_eeprom.ee_rfkill_pol;

	tasklet_init(&ah->rf_kill.toggleq, ath5k_tasklet_rfkill_toggle,
		(unsigned long)ah);

	ath5k_rfkill_disable(ah);

	/* enable interrupt for rfkill switch */
	if (AR5K_EEPROM_HDR_RFKILL(ah->ah_capabilities.cap_eeprom.ee_header))
		ath5k_rfkill_set_intr(ah, true);
}


void
ath5k_rfkill_hw_stop(struct ath5k_hw *ah)
{
	/* disable interrupt for rfkill switch */
	if (AR5K_EEPROM_HDR_RFKILL(ah->ah_capabilities.cap_eeprom.ee_header))
		ath5k_rfkill_set_intr(ah, false);

	tasklet_kill(&ah->rf_kill.toggleq);

	/* enable RFKILL when stopping HW so Wifi LED is turned off */
	ath5k_rfkill_enable(ah);
}

