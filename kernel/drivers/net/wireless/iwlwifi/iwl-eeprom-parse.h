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
#ifndef __iwl_eeprom_parse_h__
#define __iwl_eeprom_parse_h__

#include <beep/types.h>
#include <beep/if_ether.h>
#include "iwl-trans.h"

struct iwl_nvm_data {
	int n_hw_addrs;
	u8 hw_addr[ETH_ALEN];

	u8 calib_version;
	__le16 calib_voltage;

	__le16 raw_temperature;
	__le16 kelvin_temperature;
	__le16 kelvin_voltage;
	__le16 xtal_calib[2];

	bool sku_cap_band_24GHz_enable;
	bool sku_cap_band_52GHz_enable;
	bool sku_cap_11n_enable;
	bool sku_cap_amt_enable;
	bool sku_cap_ipan_enable;

	u8 radio_cfg_type;
	u8 radio_cfg_step;
	u8 radio_cfg_dash;
	u8 radio_cfg_pnum;
	u8 valid_tx_ant, valid_rx_ant;

	u16 nvm_version;
	s8 max_tx_pwr_half_dbm;

	struct ieee80211_supported_band bands[IEEE80211_NUM_BANDS];
	struct ieee80211_channel channels[];
};

/**
 * iwl_parse_eeprom_data - parse EEPROM data and return values
 *
 * @dev: device pointer we're parsing for, for debug only
 * @cfg: device configuration for parsing and overrides
 * @eeprom: the EEPROM data
 * @eeprom_size: length of the EEPROM data
 *
 * This function parses all EEPROM values we need and then
 * returns a (newly allocated) struct containing all the
 * relevant values for driver use. The struct must be freed
 * later with iwl_free_nvm_data().
 */
struct iwl_nvm_data *
iwl_parse_eeprom_data(struct device *dev, const struct iwl_cfg *cfg,
		      const u8 *eeprom, size_t eeprom_size);

/**
 * iwl_free_nvm_data - free NVM data
 * @data: the data to free
 */
static inline void iwl_free_nvm_data(struct iwl_nvm_data *data)
{
	kfree(data);
}

int iwl_nvm_check_version(struct iwl_nvm_data *data,
			  struct iwl_trans *trans);

#endif /* __iwl_eeprom_parse_h__ */
