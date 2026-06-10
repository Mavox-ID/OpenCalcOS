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
/**************\
* Capabilities *
\**************/

#include "ath5k.h"
#include "reg.h"
#include "debug.h"
#include "../regd.h"

/*
 * Fill the capabilities struct
 * TODO: Merge this with EEPROM code when we are done with it
 */
int ath5k_hw_set_capabilities(struct ath5k_hw *ah)
{
	struct ath5k_capabilities *caps = &ah->ah_capabilities;
	u16 ee_header;

	/* Capabilities stored in the EEPROM */
	ee_header = caps->cap_eeprom.ee_header;

	if (ah->ah_version == AR5K_AR5210) {
		/*
		 * Set radio capabilities
		 * (The AR5110 only supports the middle 5GHz band)
		 */
		caps->cap_range.range_5ghz_min = 5120;
		caps->cap_range.range_5ghz_max = 5430;
		caps->cap_range.range_2ghz_min = 0;
		caps->cap_range.range_2ghz_max = 0;

		/* Set supported modes */
		__set_bit(AR5K_MODE_11A, caps->cap_mode);
	} else {
		/*
		 * XXX The transceiver supports frequencies from 4920 to 6100MHz
		 * XXX and from 2312 to 2732MHz. There are problems with the
		 * XXX current ieee80211 implementation because the IEEE
		 * XXX channel mapping does not support negative channel
		 * XXX numbers (2312MHz is channel -19). Of course, this
		 * XXX doesn't matter because these channels are out of the
		 * XXX legal range.
		 */

		/*
		 * Set radio capabilities
		 */

		if (AR5K_EEPROM_HDR_11A(ee_header)) {
			if (ath_is_49ghz_allowed(caps->cap_eeprom.ee_regdomain))
				caps->cap_range.range_5ghz_min = 4920;
			else
				caps->cap_range.range_5ghz_min = 5005;
			caps->cap_range.range_5ghz_max = 6100;

			/* Set supported modes */
			__set_bit(AR5K_MODE_11A, caps->cap_mode);
		}

		/* Enable  802.11b if a 2GHz capable radio (2111/5112) is
		 * connected */
		if (AR5K_EEPROM_HDR_11B(ee_header) ||
		    (AR5K_EEPROM_HDR_11G(ee_header) &&
		     ah->ah_version != AR5K_AR5211)) {
			/* 2312 */
			caps->cap_range.range_2ghz_min = 2412;
			caps->cap_range.range_2ghz_max = 2732;

			/* Override 2GHz modes on SoCs that need it
			 * NOTE: cap_needs_2GHz_ovr gets set from
			 * ath_ahb_probe */
			if (!caps->cap_needs_2GHz_ovr) {
				if (AR5K_EEPROM_HDR_11B(ee_header))
					__set_bit(AR5K_MODE_11B,
							caps->cap_mode);

				if (AR5K_EEPROM_HDR_11G(ee_header) &&
				ah->ah_version != AR5K_AR5211)
					__set_bit(AR5K_MODE_11G,
							caps->cap_mode);
			}
		}
	}

	if ((ah->ah_radio_5ghz_revision & 0xf0) == AR5K_SREV_RAD_2112)
		__clear_bit(AR5K_MODE_11A, caps->cap_mode);

	/* Set number of supported TX queues */
	if (ah->ah_version == AR5K_AR5210)
		caps->cap_queues.q_tx_num = AR5K_NUM_TX_QUEUES_NOQCU;
	else
		caps->cap_queues.q_tx_num = AR5K_NUM_TX_QUEUES;

	/* Newer hardware has PHY error counters */
	if (ah->ah_mac_srev >= AR5K_SREV_AR5213A)
		caps->cap_has_phyerr_counters = true;
	else
		caps->cap_has_phyerr_counters = false;

	/* MACs since AR5212 have MRR support */
	if (ah->ah_version == AR5K_AR5212)
		caps->cap_has_mrr_support = true;
	else
		caps->cap_has_mrr_support = false;

	return 0;
}

/*
 * TODO: Following functions should be part of a new function
 * set_capability
 */

int ath5k_hw_enable_pspoll(struct ath5k_hw *ah, u8 *bssid,
		u16 assoc_id)
{
	if (ah->ah_version == AR5K_AR5210) {
		AR5K_REG_DISABLE_BITS(ah, AR5K_STA_ID1,
			AR5K_STA_ID1_NO_PSPOLL | AR5K_STA_ID1_DEFAULT_ANTENNA);
		return 0;
	}

	return -EIO;
}

int ath5k_hw_disable_pspoll(struct ath5k_hw *ah)
{
	if (ah->ah_version == AR5K_AR5210) {
		AR5K_REG_ENABLE_BITS(ah, AR5K_STA_ID1,
			AR5K_STA_ID1_NO_PSPOLL | AR5K_STA_ID1_DEFAULT_ANTENNA);
		return 0;
	}

	return -EIO;
}
